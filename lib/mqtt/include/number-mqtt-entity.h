#ifndef NUMBER_ENTITY_H
#define NUMBER_ENTITY_H
#include <PubSubClient.h>
#include "mqtt-entity.h"
#include "base-mqtt-entity.h"

class NumberMqttEntity : public BaseMqttEntity
{

private:
    MqttEntity entity;

public:
    NumberMqttEntity(
        PubSubClient *client,
        const char *uniqueId,
        const char *friendlyName,
        const char *discoveryPrefix,
        const char *deviceClass,
        const char *defaultState);

    void initialise() override;
    void setState(const String &state);
    String state() override;
    void receiveMqttMessage(char *topic, byte *message, unsigned int length) override;
    String id() const override;
    JsonDocument config() const override;
};

#endif