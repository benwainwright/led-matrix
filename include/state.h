#ifndef STATE_H
#define STATE_H

#include "Arduino.h"
#include "mqtt/number-mqtt-entity.h"
#include "mqtt/select-mqtt-entity.h"
#include "mqtt/mqtt-device.h"
#include "mqtt/mqtt-notify.h"
#include "constants.h"

class State
{

private:
    PubSubClient *client;
    String mediaTitle;
    String mediaArtist;
    bool mediaPlaying;
    SemaphoreHandle_t mutex;
    MqttDevice device;
    NumberMqttEntity brightnessControl;
    SelectMqttEntity pageSelector;
    NotifyMqttEntity notifyEntity;
    String notification;

    bool ensureMutex();

public:
    State(PubSubClient *initClient);
    void initialise();
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
    u_int8_t brightness();
    String page();
    String title();
    String artist();
    String notify();
    bool playing();
};

#endif