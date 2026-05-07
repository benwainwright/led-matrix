#ifndef GLOBALS_H
#define GLOBALS_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "constants.h"
#include "state.h"
#include "clock.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

extern WiFiClient espClient;
extern PubSubClient client;
extern std::unique_ptr<MatrixPanel_I2S_DMA> display;
extern TaskHandle_t finishedDataInitialisationHandle;
extern Clock theClock;
extern State state;

#endif