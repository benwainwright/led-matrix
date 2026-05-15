#include "data.h"
#include <Arduino.h>
#include <Config.h>
#include <Components.h>
#include <Mqtt.h>
#include "run_mqtt.h"
#include "app.h"
#include "wifi_setup.h"

void dataLoop(void *parameter)
{

    App *app = static_cast<App *>(parameter);
    Serial.println("Initialising data loop");
    vTaskDelay(pdMS_TO_TICKS(1000));
    setupWifi();
    app->config.start();
    setupMqtt(app);
    if (app->finishedDataInitialisationHandle == nullptr)
    {
        Serial.println("Display task handle is not available");
    }
    else
    {
        xTaskNotifyGive(app->finishedDataInitialisationHandle);
    }

    while (true)
    {
        maintainMqttConnection(app);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
