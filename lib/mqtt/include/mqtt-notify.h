
#ifndef NOTIFY_ENTITY_H
#define NOTIFY_ENTITY_H
#include <PubSubClient.h>
#include "mqtt-entity.h"
#include "base-mqtt-entity.h"

class NotifyMqttEntity : public BaseMqttEntity
{

private:
    MqttEntity entity;

public:
    NotifyMqttEntity(
        PubSubClient *client,
        const char *uniqueId,
        const char *friendlyName,
        const char *discoveryPrefix);

    void initialise() override;
    String state() override;
    void receiveMqttMessage(char *topic, byte *message, unsigned int length) override;
    String id() const override;
    JsonDocument config() const override;
};

#endif