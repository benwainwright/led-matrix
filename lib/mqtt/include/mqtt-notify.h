
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

    void initialise();
    String state();
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
    String id() const;
    JsonDocument config() const;
};

#endif