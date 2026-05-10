#ifndef MQTT_ENTITY_H
#define MQTT_ENTITY_H

#include "mqtt/base-mqtt-entity.h"
#include <ArduinoJson.h>
#include <PubSubClient.h>

#define HOMEASSISTANT_STATUS_TOPIC "homeassistant/status"

class MqttEntity : BaseMqttEntity
{
private:
    PubSubClient *client;
    const char *uniqueId;
    const char *friendlyName;
    const char *discoveryPrefix;
    const char *deviceClass;
    const char *defaultState;
    const char *type;

    JsonDocument additionalConfig;
    String stateValue;
    SemaphoreHandle_t mutex;
    String stateTopic;
    String commandTopic;

    bool compareMessage(byte *message, const char *expected, unsigned int length);
    bool ensureMutex();

public:
    String state();
    void setState(String state);
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
    void addAdditionalConfiguration(JsonDocument config);
    JsonDocument config();
    String id();

    MqttEntity(
        PubSubClient *client,
        const char *uniqueId,
        const char *friendlyName,
        const char *discoveryPrefix,
        const char *deviceClass,
        const char *defaultState,
        const char *type);

    void initialise();
};

#endif
