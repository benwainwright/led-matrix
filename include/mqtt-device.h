#ifndef MQTT_DEVICE_H
#define MQTT_DEVICE_H

#include "base-mqtt-entity.h"
#include <PubSubClient.h>

class MqttDevice
{
private:
    std::vector<BaseMqttEntity *> entities;
    SemaphoreHandle_t mutex;
    PubSubClient *client;
    const char *discoveryPrefix;
    const char *deviceId;
    const char *name;

    const char *originName;
    const char *swVersion;
    const char *supportUrl;
    bool ensureMutex();
    bool compareMessage(byte *message, const char *expected, unsigned int length);
    void triggerDiscovery();

public:
    MqttDevice(
        PubSubClient *initClient,
        const std::vector<BaseMqttEntity *> entities,
        const char *deviceId,
        const char *name,
        const char *originName,
        const char *swVersion,
        const char *supportUrl,
        const char *initDiscoveryPrefix);

    void initialise();
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
};

#endif