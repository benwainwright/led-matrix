#include "state.h"
#include "app.h"
#include "constants.h"
#include <Arduino.h>
#include <Mqtt.h>

State::State(PubSubClient* initClient)
    : client(initClient), mediaPlaying(false), mutex(nullptr),
      brightnessControl(NumberMqttEntity(initClient, "led-matrix-brightness", "Screen Brightness",
                                         "homeassistant", nullptr, "100")),

      pageSelector(SelectMqttEntity(initClient, "led-matrix-page", "Page", "homeassistant", nullptr,
                                    {CLOCK_PAGE, MEDIA_PAGE, TRAINS_PAGE}, CLOCK_PAGE)),

      notifyEntity({NotifyMqttEntity(initClient, "led-matrix-notify", "Page", "homeassistant")

      }),
      device(MqttDevice(initClient, {&brightnessControl, &pageSelector, &notifyEntity},
                        "matrix-led-device", "LED Matrix Display", "Ben Wainwright", "0.0.1",
                        "https://github.com/benwainwright/led-matrix", "homeassistant")) {}

bool State::ensureMutex() {
  if (mutex != nullptr) {
    return true;
  }

  mutex = xSemaphoreCreateMutex();
  if (mutex == nullptr) {
    Serial.println("Failed to create MQTT entity mutex");
    return false;
  }

  return true;
}

void State::initialise(App* app) {
  device.initialise();
  artistTopic = app->config.getValue(ARTISTS_TOPIC_FIELD_NAME);
  client->subscribe(artistTopic.c_str());

  titleTopic = app->config.getValue(TITLE_TOPIC_FIELD_NAME);
  client->subscribe(titleTopic.c_str());

  statusTopic = app->config.getValue(STATUS_TOPIC_FIELD_NAME);
  client->subscribe(statusTopic.c_str());
}

void State::receiveMqttMessage(char* topic, byte* message, unsigned int length) {
  if (!ensureMutex()) {
    return;
  }

  device.receiveMqttMessage(topic, message, length);
  String snapshot = String((char*)message, length);
  if (std::string(topic) == artistTopic) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      mediaArtist = snapshot;
      xSemaphoreGive(mutex);
    }
  }

  if (std::string(topic) == titleTopic) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      mediaTitle = snapshot;
      xSemaphoreGive(mutex);
    }
  }

  if (std::string(topic) == statusTopic) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      Serial.println(snapshot);
      mediaPlaying = snapshot == "playing";
      xSemaphoreGive(mutex);
    }
  }
}

uint8_t State::brightness() {

  auto rawState = brightnessControl.state();
  return rawState.length() > 0 ? constrain(rawState.toInt(), 0L, 255L) : 100;
}

String State::page() { return pageSelector.state(); }

String State::artist() {
  String snapshot;
  if (!ensureMutex()) {
    return snapshot;
  }

  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    snapshot = mediaArtist;
    xSemaphoreGive(mutex);
  }
  return snapshot;
}

String State::title() {
  String snapshot;
  if (!ensureMutex()) {
    return snapshot;
  }

  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    snapshot = mediaTitle;
    xSemaphoreGive(mutex);
  }
  return snapshot;
}

String State::notify() { return notifyEntity.state(); }

bool State::playing() {
  bool snapshot = false;
  if (!ensureMutex()) {
    return snapshot;
  }

  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    snapshot = mediaPlaying;
    xSemaphoreGive(mutex);
  }
  return snapshot;
}
