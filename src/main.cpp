#include <Mqtt.h>

#include "app.h"
#include "data.h"
#include "display.h"
#include "run_trains_loop.h"
#include "wifi_setup.h"

static App app;

void setup() {
  Serial.begin(115200);

  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  app.finishedDataInitialisationEventGroup = xEventGroupCreate();
  app.departuresMutex = xSemaphoreCreateMutex();

  if (app.departuresMutex == nullptr) {
    Serial.println("Failed to create departures mutex");
    return;
  }

  if (xTaskCreatePinnedToCore(displayLoop, "Display Loop", 4096, &app, 3, nullptr, 0) != pdPASS) {
    Serial.println("Failed to create display task");
    return;
  }

  if (xTaskCreate(runTrainLoop, "Trains Task", 12288, &app, 1, nullptr) != pdPASS) {
    Serial.println("Failed to create data task");
  }

  if (xTaskCreate(dataLoop, "Data Task", 4096, &app, 1, nullptr) != pdPASS) {
    Serial.println("Failed to create data task");
  }
}

void loop() {
  // Noop
}
