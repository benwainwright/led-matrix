#ifndef MQTT_ENTITY_H
#define MQTT_ENTITY_H

#include <ArduinoJson.h>
#include <PubSubClient.h>

#define HOMEASSISTANT_STATUS_TOPIC "homeassistant/status"

class MqttEntity
{
private:
    PubSubClient *client;
    const char *uniqueId;
    const char *friendlyName;
    const char *discoveryPrefix;
    const char *deviceClass;
    const char *defaultState;
    const char *type;
    String stateValue;
    SemaphoreHandle_t mutex;
    String stateTopic;
    String commandTopic;

    void triggerDiscovery();
    bool compareMessage(byte *message, const char *expected, unsigned int length);
    bool ensureMutex();

public:
    String state();
    void setState(String state);
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
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
