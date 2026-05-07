#include <PubSubClient.h>

#include "mqtt-entity.h"
#include "number-mqtt-entity.h"

NumberMqttEntity::NumberMqttEntity(
    PubSubClient *client,
    const char *uniqueId,
    const char *friendlyName,
    const char *discoveryPrefix,
    const char *deviceClass,
    const char *defaultState

    ) : entity(MqttEntity(client,
                          uniqueId,
                          friendlyName,
                          discoveryPrefix,
                          deviceClass,
                          defaultState,
                          "number"))
{
}

void NumberMqttEntity::initialise()
{
    entity.initialise();
}

JsonDocument NumberMqttEntity::config()
{
    return entity.config();
}

void NumberMqttEntity::setState(String state)
{
    entity.setState(state);
}

String NumberMqttEntity::id()
{
    return entity.id();
}

String NumberMqttEntity::state()
{
    return entity.state();
}

void NumberMqttEntity::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    entity.receiveMqttMessage(topic, message, length);
}