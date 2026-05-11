#include "data.h"
#include <Arduino.h>
#include <Components.h>
#include <Mqtt.h>
#include "run_mqtt.h"
#include "wifi_setup.h"

void dataLoop(void *parameter)
{
    Serial.println("Initialising data loop");
    vTaskDelay(pdMS_TO_TICKS(1000));
    setupWifi();
    setupMqtt();
    if (finishedDataInitialisationHandle == nullptr)
    {
        Serial.println("Display task handle is not available");
    }
    else
    {
        xTaskNotifyGive(finishedDataInitialisationHandle);
    }

    while (true)
    {
        maintainMqttConnection();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
