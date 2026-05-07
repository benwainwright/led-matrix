#include <Arduino.h>
#include "number-mqtt-entity.h"
#include "select-mqtt-entity.h"
#include "constants.h"
#include "state.h"

State::State(PubSubClient *initClient) : client(initClient),
                                         brightnessControl(
                                             NumberMqttEntity(
                                                 initClient,
                                                 "led-matrix-brightness",
                                                 "Screen Brightness",
                                                 "homeassistant",
                                                 nullptr,
                                                 "100")),

                                         pageSelector(
                                             SelectMqttEntity(
                                                 initClient,
                                                 "led-matrix-page",
                                                 "Page",
                                                 "homeassistant",
                                                 nullptr,
                                                 {CLOCK_PAGE, MEDIA_PAGE},
                                                 CLOCK_PAGE)),
                                         device(MqttDevice(initClient, {&brightnessControl, &pageSelector}, "matrix-led-device", "LED Matrix Display",
                                                           "Ben Wainwright", "0.0.1", "https://github.com/benwainwright/led-matrix",
                                                           "homeassistant"))
{
}

bool State::ensureMutex()
{
    if (mutex != nullptr)
    {
        return true;
    }

    mutex = xSemaphoreCreateMutex();
    if (mutex == nullptr)
    {
        Serial.println("Failed to create MQTT entity mutex");
        return false;
    }

    return true;
}

void State::initialise()
{
    device.initialise();
    client->subscribe("homeassistant/media_players/media_player.living_room/artist");
    client->subscribe("homeassistant/media_players/media_player.living_room/title");
    client->subscribe("homeassistant/media_players/media_player.living_room/status");
}

void State::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    if (!ensureMutex())
    {
        return;
    }

    device.receiveMqttMessage(topic, message, length);
    String snapshot = String((char *)message, length);
    if (String(topic) == "homeassistant/media_players/media_player.living_room/artist")
    {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
        {
            mediaArtist = snapshot;
            xSemaphoreGive(mutex);
        }
    }

    if (String(topic) == "homeassistant/media_players/media_player.living_room/title")
    {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
        {
            mediaTitle = snapshot;
            xSemaphoreGive(mutex);
        }
    }

    if (String(topic) == "homeassistant/media_players/media_player.living_room/status")
    {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
        {
            Serial.println(snapshot);
            mediaPlaying = snapshot == "playing";
            xSemaphoreGive(mutex);
        }
    }
}

u_int8_t State::brightness()
{

    auto rawState = brightnessControl.state();
    return rawState.length() > 0 ? constrain(rawState.toInt(), 0L, 255L) : 100;
}

String State::page()
{
    return pageSelector.state();
}

String State::artist()
{
    String snapshot;
    if (!ensureMutex())
    {
        return snapshot;
    }

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
    {
        snapshot = mediaArtist;
        xSemaphoreGive(mutex);
    }
    return snapshot;
}

String State::title()
{
    String snapshot;
    if (!ensureMutex())
    {
        return snapshot;
    }

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
    {
        snapshot = mediaTitle;
        xSemaphoreGive(mutex);
    }
    return snapshot;
}

bool State::playing()
{
    bool snapshot;
    if (!ensureMutex())
    {
        return snapshot;
    }

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE)
    {
        snapshot = mediaPlaying;
        xSemaphoreGive(mutex);
    }
    return snapshot;
}