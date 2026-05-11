#ifndef GLOBALS_H
#define GLOBALS_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "state.h"

extern WiFiClient espClient;
extern PubSubClient client;
extern std::unique_ptr<MatrixPanel_I2S_DMA> display;
extern TaskHandle_t finishedDataInitialisationHandle;
extern State state;

#endif