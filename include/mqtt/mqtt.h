#ifndef MQTT_H
#define MQTT_H

#include "globals.h"

void maintainMqttConnection();
void setupMqtt();
void messageReceivedCallback(char *topic, byte *message, unsigned int length);

#endif