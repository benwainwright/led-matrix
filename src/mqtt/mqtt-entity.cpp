#include "mqtt/mqtt-entity.h"
#include "Arduino.h"

void merge(JsonVariant dst, JsonVariantConst src)
{
    if (src.isNull())
    {
        return;
    }

    if (src.is<JsonObjectConst>())
    {
        for (JsonPairConst kvp : src.as<JsonObjectConst>())
        {
            if (dst[kvp.key()])
                merge(dst[kvp.key()], kvp.value());
            else
                dst[kvp.key()] = kvp.value();
        }
    }
    else
    {
        dst.set(src);
    }
}

MqttEntity::MqttEntity(
    PubSubClient *initClient,
    const char *initUniqueId,
    const char *initFriendlyName,
    const char *initDiscoveryPrefix,
    const char *initDeviceClass,
    const char *initDefaultState,
    const char *initType) : client(initClient), uniqueId(initUniqueId), friendlyName(initFriendlyName), discoveryPrefix(initDiscoveryPrefix), deviceClass(initDeviceClass), type(initType), stateValue(initDefaultState == nullptr ? "" : initDefaultState), mutex(nullptr)
{
    String slash = "/";
    String deviceClassString = deviceClass == nullptr ? "" : deviceClass + slash;

    stateTopic = discoveryPrefix + slash + uniqueId + slash + type + slash + deviceClassString + "state";
    commandTopic = discoveryPrefix + slash + uniqueId + slash + type + slash + deviceClassString + "set";
}

void MqttEntity::addAdditionalConfiguration(JsonDocument config)
{
    additionalConfig = config;
}

bool MqttEntity::compareMessage(byte *message, const char *expected, unsigned int length)
{

    return (length == strlen(expected) &&
            memcmp(message, expected, length) == 0);
}

JsonDocument MqttEntity::config()
{
    String slash = "/";

    String discoveryTopic = discoveryPrefix + slash + type + slash + uniqueId + slash + "config";

    JsonDocument config;
    config["device_class"] = deviceClass;
    config["state_topic"] = stateTopic;
    config["unique_id"] = uniqueId;
    config["platform"] = type;
    config["command_topic"] = commandTopic;
    config["name"] = friendlyName;

    merge(config, additionalConfig);

    return config;
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

void MqttEntity::initialise()
{
    if (!ensureMutex())
    {
        return;
    }

    const bool subscribed = client->subscribe(stateTopic.c_str());
    Serial.print("MQTT state subscribe ");
    Serial.print(subscribed ? "succeeded: " : "failed: ");
    Serial.println(stateTopic.c_str());

    const bool commandSubscribed = client->subscribe(commandTopic.c_str());
    Serial.print("MQTT command subscribe ");
    Serial.print(commandSubscribed ? "succeeded: " : "failed: ");
    Serial.println(commandTopic.c_str());

    String currentState = state();
    client->publish(stateTopic.c_str(), currentState.c_str(), currentState.length());
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

String MqttEntity::id()
{
    return String(uniqueId);
}

void MqttEntity::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    if (String(topic) == commandTopic)
    {
        String newState((const char *)message, length);
        setState(newState);
    }
}
