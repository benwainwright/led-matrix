#include "globals.h"
#include "wifi_setup.h"
#include "display.h"
#include "mqtt.h"
#include "data.h"
#include "clock.h"
#include "mqtt-entity.h"

WiFiClient espClient;
PubSubClient client(espClient);
std::unique_ptr<MatrixPanel_I2S_DMA> display;
TaskHandle_t finishedDataInitialisationHandle;

Clock theClock;

State state = State(&client);

void setup()
{
  Serial.begin(115200);

  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  if (xTaskCreatePinnedToCore(
          displayLoop,
          "Display Loop",
          4096,
          nullptr,
          1,
          &finishedDataInitialisationHandle,
          0) != pdPASS)
  {
    Serial.println("Failed to create display task");
    return;
  }

  if (xTaskCreatePinnedToCore(
          dataLoop,
          "Data Task",
          4096,
          nullptr,
          1,
          nullptr,
          1) != pdPASS)
  {
    Serial.println("Failed to create data task");
  }
}

void loop()
{
  // Noop
}
