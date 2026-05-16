#ifndef APP_H
#define APP_H

#include "state.h"
#include <Config.h>
#include <DNSServer.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <rtt.h>
#include <string>

struct App {
  WiFiClient wifi;
  PubSubClient mqtt;
  ConfigServer config;
  DNSServer dns;
  std::vector<Departure> departures;
  bool accessPointModeOn;
  std::shared_ptr<MatrixPanel_I2S_DMA> display;
  EventGroupHandle_t finishedDataInitialisationEventGroup;
  State state;
  App()
      : wifi(), mqtt(wifi), accessPointModeOn(false), display(nullptr),
        finishedDataInitialisationEventGroup(nullptr), state(&mqtt) {}
};

#define DATA_READY_BIT BIT0

#endif
