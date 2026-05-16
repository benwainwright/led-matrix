#include "data.h"
#include "app.h"
#include "run_mqtt.h"
#include "wifi_setup.h"
#include <Arduino.h>
#include <Components.h>
#include <Config.h>
#include <Mqtt.h>

void dataLoop(void* parameter) {
  auto app = static_cast<App*>(parameter);
  Serial.println("Initialising data loop");
  vTaskDelay(pdMS_TO_TICKS(1000));
  setupConfigServer(app);
  auto wifiResult = setupWifi(app);
  app->config.start();
  if (!wifiResult) {
    while (true) {
      app->dns.processNextRequest();
    }
  } else {
    setupMqtt(app);
    xEventGroupSetBits(app->finishedDataInitialisationEventGroup, DATA_READY_BIT);

    while (true) {
      maintainMqttConnection(app);
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}
