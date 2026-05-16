#ifndef MQTT_ENTITY_H
#define MQTT_ENTITY_H

#include "base-mqtt-entity.h"
#include <ArduinoJson.h>
#include <PubSubClient.h>

#define HOMEASSISTANT_STATUS_TOPIC "homeassistant/status"

class MqttEntity : public BaseMqttEntity {
private:
  PubSubClient* client;
  const char* uniqueId;
  const char* friendlyName;
  const char* discoveryPrefix;
  const char* deviceClass;
  const char* defaultState;
  const char* type;

  JsonDocument additionalConfig;
  String stateValue;
  SemaphoreHandle_t mutex;
  String stateTopic;
  String commandTopic;

  bool compareMessage(byte* message, const char* expected, unsigned int length) const;
  bool ensureMutex();

public:
  MqttEntity(PubSubClient* client, const char* uniqueId, const char* friendlyName,
             const char* discoveryPrefix, const char* deviceClass, const char* defaultState,
             const char* type);

  String state();
  JsonDocument config() const;
  String id() const;

  void setState(const String& state);
  void receiveMqttMessage(char* topic, byte* message, unsigned int length);
  void addAdditionalConfiguration(const JsonDocument& config);

  void initialise();
};

#endif
