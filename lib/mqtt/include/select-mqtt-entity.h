#ifndef SELECT_ENTITY_H
#define SELECT_ENTITY_H

#include <PubSubClient.h>
#include "mqtt-entity.h"
#include "base-mqtt-entity.h"

class SelectMqttEntity : public BaseMqttEntity
{

private:
    MqttEntity entity;

public:
    SelectMqttEntity(
        PubSubClient *client,
        const char *uniqueId,
        const char *friendlyName,
        const char *discoveryPrefix,
        const char *deviceClass,
        std::vector<const char *> options,
        const char *defaultState);

    JsonDocument config() const;
    void initialise();
    void setState(const String &state);
    String id() const;

    String state();
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
};
#endif