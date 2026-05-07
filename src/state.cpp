#include <Arduino.h>
#include "number-mqtt-entity.h"
#include "select-mqtt-entity.h"
#include "constants.h"
#include "state.h"

State::State(PubSubClient *initClient) : brightnessControl(
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
                                                 {CLOCK_PAGE, DASHBOARD_PAGE},
                                                 CLOCK_PAGE)),
                                         device(MqttDevice(initClient, {&brightnessControl, &pageSelector}, "matrix-led-device", "LED Matrix Display",
                                                           "Ben Wainwright", "0.0.1", "https://github.com/benwainwright/led-matrix",
                                                           "homeassistant"))
{
}

void State::initialise()
{
    device.initialise();
}

void State::receiveMqttMessage(char *topic, byte *message, unsigned int length)
{
    device.receiveMqttMessage(topic, message, length);
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