#include "mqtt-entity.h"
#include "Arduino.h"

MqttEntity::MqttEntity(
    PubSubClient *initClient,
    const char *initUniqueId,
    const char *initFriendlyName,
    const char *initDiscoveryPrefix,
    const char *initDeviceClass,
    const char *initDefaultState,
    const char *initType) : client(initClient), uniqueId(initUniqueId), friendlyName(initFriendlyName), discoveryPrefix(initDiscoveryPrefix), deviceClass(initDeviceClass), type(initType), defaultState(initDefaultState), stateValue(initDefaultState == nullptr ? "" : initDefaultState), mutex(nullptr)
{
    String slash = "/";
    String deviceClassString = deviceClass == nullptr ? "" : deviceClass + slash;

    stateTopic = discoveryPrefix + slash + uniqueId + slash + type + slash + deviceClassString + "state";
    commandTopic = discoveryPrefix + slash + uniqueId + slash + type + slash + deviceClassString + "set";
}

bool MqttEntity::compareMessage(byte *message, const char *expected, unsigned int length)
{

    return (length == strlen(expected) &&
            memcmp(message, expected, length) == 0);
}

bool MqttEntity::ensureMutex()
{
    if (mutex != nullptr)
    {
        return true;
    }

    mutex = xSemaphoreCreateMutex();
    if (mutex == nullptr)
    {
        Serial.println("Failed to create MQTT entity mutex");
        return false;
    }

    return true;
}

void MqttEntity::triggerDiscovery()
{

    String slash = "/";

    String discoveryTopic = discoveryPrefix + slash + type + slash + uniqueId + slash + "config";

    JsonDocument config;
    config["device_class"] = deviceClass;
    config["state_topic"] = stateTopic;
    config["unique_id"] = uniqueId;

    String deviceUnderscore = "device_";
    config["device"]["identifiers"][0] = deviceUnderscore + uniqueId;
    config["device"]["name"] = friendlyName;
    config["command_topic"] = commandTopic;
    config["friendly_name"] = friendlyName;

    String json;

    serializeJson(config, json);

    Serial.print("Publishing MQTT discovery topic: ");
    Serial.println(discoveryTopic.c_str());

    Serial.print("Publishing MQTT discovery payload bytes: ");
    Serial.println(json.length());

    const bool published = client->publish(discoveryTopic.c_str(), json.c_str(), true);
    Serial.print("MQTT discovery publish ");
    Serial.println(published ? "succeeded" : "failed");
}

void MqttEntity::initialise()
{
    if (!ensureMutex())
    {
        return;
    }

    triggerDiscovery();
    client->subscribe(stateTopic.c_str());
    client->subscribe(commandTopic.c_str());

    setState(defaultState);

    const bool statusSubscribed = client->subscribe(HOMEASSISTANT_STATUS_TOPIC);
    Serial.print("MQTT status subscribe ");
    Serial.print(statusSubscribed ? "succeeded: " : "failed: ");
    Serial.println(HOMEASSISTANT_STATUS_TOPIC);

    const bool subscribed = client->subscribe(stateTopic.c_str());
    Serial.print("MQTT state subscribe ");
    Serial.print(subscribed ? "succeeded: " : "failed: ");
    Serial.println(stateTopic.c_str());
}

void MqttEntity::setState(String state)
{
    client->publish(stateTopic.c_str(), state.c_str(), state.length());
    if (!ensureMutex())
    {
        return;
    }

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
    {
        stateValue = state;
        xSemaphoreGive(mutex);
    }
}

String MqttEntity::state()
{
    String snapshot;
    if (!ensureMutex())
    {
        return snapshot;
    }

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
    {
        snapshot = stateValue;
        xSemaphoreGive(mutex);
    }
    return snapshot;
}

void MqttEntity::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    if (String(topic) == HOMEASSISTANT_STATUS_TOPIC && compareMessage(message, "online", length))
    {
        triggerDiscovery();
    }
    else if (String(topic) == commandTopic)
    {

        String newState((const char *)message, length);

        if (!ensureMutex())
        {
            return;
        }

        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
        {
            stateValue = newState;
            xSemaphoreGive(mutex);
        }
    }
}
