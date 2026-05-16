#include "data.h"
#include "display.h"
#include "wifi_setup.h"
#include <Mqtt.h>

#include "app.h"

static App app;

void setup() {
  Serial.begin(115200);

  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  if (xTaskCreatePinnedToCore(displayLoop, "Display Loop", 4096, &app, 1,
                              &app.finishedDataInitialisationHandle, 0) != pdPASS) {
    Serial.println("Failed to create display task");
    return;
  }

  if (xTaskCreatePinnedToCore(dataLoop, "Data Task", 4096, &app, 1, nullptr, 1) != pdPASS) {
    Serial.println("Failed to create data task");
  }
}

void loop() {
  // Noop
}
