#include <PubSubClient.h>

#include "mqtt-entity.h"
#include "mqtt-notify.h"

NotifyMqttEntity::NotifyMqttEntity(
    PubSubClient *client,
    const char *uniqueId,
    const char *friendlyName,
    const char *discoveryPrefix

    ) : entity(MqttEntity(client,
                          uniqueId,
                          friendlyName,
                          discoveryPrefix,
                          nullptr,
                          "",
                          "notify"))
{
}

void NotifyMqttEntity::initialise()
{
    entity.initialise();
}

JsonDocument NotifyMqttEntity::config() const
{
    return entity.config();
}

String NotifyMqttEntity::id() const
{
    return entity.id();
}

String NotifyMqttEntity::state()
{
    return entity.state();
}

void NotifyMqttEntity::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    entity.receiveMqttMessage(topic, message, length);
}