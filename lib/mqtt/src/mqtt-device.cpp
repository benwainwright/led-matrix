#include "base-mqtt-entity.h"
#include <ArduinoJson.h>

#include "Arduino.h"
#include "mqtt-device.h"
#include <PubSubClient.h>

#define HOMEASSISTANT_STATUS_TOPIC "homeassistant/status"

MqttDevice::MqttDevice(PubSubClient* initClient, const std::vector<BaseMqttEntity*> initEntities,
                       const char* initDeviceId, const char* initName, const char* originName,
                       const char* swVersion, const char* supportUrl,
                       const char* initDiscoveryPrefix)
    : entities(initEntities), mutex(nullptr), client(initClient),
      discoveryPrefix(initDiscoveryPrefix), deviceId(initDeviceId), name(initName),
      originName(originName), swVersion(swVersion), supportUrl(supportUrl) {}

void MqttDevice::triggerDiscovery() {
  String slash = "/";

  String topicPrefix = discoveryPrefix + slash + "device" + slash + deviceId + slash;

  String discoveryTopic = topicPrefix + "config";
  String availabilityTopic = topicPrefix + "availability";

  JsonDocument config;

  config["dev"]["name"] = name;
  config["dev"]["ids"] = deviceId;
  config["availability_topic"] = availabilityTopic;
  config["origin"]["name"] = originName;
  config["origin"]["sw_version"] = swVersion;
  config["origin"]["support_url"] = supportUrl;

  for (size_t i = 0; i < entities.size(); i++) {
    config["cmps"][entities[i]->id()] = entities[i]->config();
  }
  String json;

  serializeJson(config, json);

  Serial.print("Publishing MQTT discovery topic: ");
  Serial.println(discoveryTopic.c_str());

  Serial.print("Publishing MQTT discovery payload bytes: ");
  Serial.println(json.length());

  const bool published = client->publish(discoveryTopic.c_str(), json.c_str(), true);
  client->publish(availabilityTopic.c_str(), "online", true);
  Serial.print("MQTT discovery publish ");
  Serial.println(published ? "succeeded" : "failed");
}

bool MqttDevice::compareMessage(byte* message, const char* expected, unsigned int length) const {

  return (length == strlen(expected) && memcmp(message, expected, length) == 0);
}

void MqttDevice::initialise() {
  if (!ensureMutex()) {
    return;
  }

  triggerDiscovery();

  const bool statusSubscribed = client->subscribe(HOMEASSISTANT_STATUS_TOPIC);
  Serial.print("MQTT status subscribe ");
  Serial.print(statusSubscribed ? "succeeded: " : "failed: ");
  Serial.println(HOMEASSISTANT_STATUS_TOPIC);

  for (size_t i = 0; i < entities.size(); i++) {
    entities[i]->initialise();
  }
}

bool MqttDevice::ensureMutex() {
  if (mutex != nullptr) {
    return true;
  }

  mutex = xSemaphoreCreateMutex();
  if (mutex == nullptr) {
    Serial.println("Failed to create MQTT entity mutex");
    return false;
  }

  return true;
}

void MqttDevice::receiveMqttMessage(char* topic, byte* message, unsigned int length) {
  if (String(topic) == HOMEASSISTANT_STATUS_TOPIC && compareMessage(message, "online", length)) {
    triggerDiscovery();
  }
  for (size_t i = 0; i < entities.size(); i++) {
    entities[i]->receiveMqttMessage(topic, message, length);
  }
}
