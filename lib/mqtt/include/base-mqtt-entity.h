#ifndef BASEMQTT_H
#define BASEMQTT_H
#include <Arduino.h>
#include <ArduinoJson.h>

class BaseMqttEntity
{
public:
    virtual ~BaseMqttEntity() = default;
    virtual String state() = 0;
    virtual JsonDocument config() const = 0;
    virtual void initialise() = 0;
    virtual void receiveMqttMessage(char *topic, byte *message, unsigned int length) = 0;
    virtual String id() const = 0;
};

#endif