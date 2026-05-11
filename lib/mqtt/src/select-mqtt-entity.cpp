#include <PubSubClient.h>

#include "mqtt-entity.h"
#include "select-mqtt-entity.h"

SelectMqttEntity::SelectMqttEntity(
    PubSubClient *client,
    const char *uniqueId,
    const char *friendlyName,
    const char *discoveryPrefix,
    const char *deviceClass,
    const std::vector<const char *> options,
    const char *defaultState) : entity(MqttEntity(client,
                                                  uniqueId,
                                                  friendlyName,
                                                  discoveryPrefix,
                                                  deviceClass,
                                                  defaultState,
                                                  "select"))
{
    JsonDocument config;
    JsonArray optionsArray = config["options"].to<JsonArray>();
    for (size_t i = 0; i < options.size(); i++)
    {
        optionsArray.add(options[i]);
    }

    entity.addAdditionalConfiguration(config);
}

JsonDocument SelectMqttEntity::config()
{
    return entity.config();
}

void SelectMqttEntity::initialise()
{
    entity.initialise();
}

void SelectMqttEntity::setState(String state)
{
    entity.setState(state);
}

String SelectMqttEntity::id()
{
    return entity.id();
}

String SelectMqttEntity::state()
{
    return entity.state();
}

void SelectMqttEntity::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    entity.receiveMqttMessage(topic, message, length);
}