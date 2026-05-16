#ifndef APP_H
#define APP_H

#include "state.h"
#include <Config.h>
#include <DNSServer.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <string>

struct App {
  WiFiClient wifi;
  PubSubClient mqtt;
  ConfigServer config;
  DNSServer dns;
  bool accessPointModeOn;
  std::shared_ptr<MatrixPanel_I2S_DMA> display;
  TaskHandle_t finishedDataInitialisationHandle;
  State state;
  App()
      : wifi(), mqtt(wifi), accessPointModeOn(false), display(nullptr),
        finishedDataInitialisationHandle(nullptr), state(&mqtt) {}
};

#endif
