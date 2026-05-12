#ifndef APP_H
#define APP_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "state.h"

struct App
{
    WiFiClient wifi;
    PubSubClient mqtt;
    std::shared_ptr<MatrixPanel_I2S_DMA> display;
    TaskHandle_t finishedDataInitialisationHandle;
    State state;
    App()
        : wifi(),
          mqtt(wifi),
          display(nullptr),
          state(&mqtt)
    {
    }
};

#endif