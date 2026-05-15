#ifndef APP_H
#define APP_H

#include <WiFi.h>
#include <Config.h>
#include <PubSubClient.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "state.h"
#include "text-field.h"

inline std::vector<std::unique_ptr<Field>> fields()
{
    std::vector<std::unique_ptr<Field>> result;
    result.push_back(std::make_unique<TextField>("ssid", "Wifi SSID"));
    result.push_back(std::make_unique<TextField>("password", "Wifi Password"));
    return result;
}

struct App
{
    WiFiClient wifi;
    PubSubClient mqtt;
    ConfigServer config;
    std::shared_ptr<MatrixPanel_I2S_DMA> display;
    TaskHandle_t finishedDataInitialisationHandle;
    State state;
    App()
        : wifi(),
          mqtt(wifi),
          config(std::make_unique<Form>(fields())),
          display(nullptr),
          state(&mqtt)
    {
    }
};

#endif