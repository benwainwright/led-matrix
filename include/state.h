#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#include "constants.h"
#include <Mqtt.h>

class App;

class State {

private:
  PubSubClient* client;
  bool mediaPlaying;
  SemaphoreHandle_t mutex;
  NumberMqttEntity brightnessControl;
  SelectMqttEntity pageSelector;
  NotifyMqttEntity notifyEntity;
  MqttDevice device;
  String mediaTitle;
  std::string artistTopic;
  std::string titleTopic;
  std::string statusTopic;
  String mediaArtist;
  String notification;

  bool ensureMutex();

public:
  State(PubSubClient* initClient);
  void initialise(App* app);
  void receiveMqttMessage(char* topic, byte* message, unsigned int length);
  uint8_t brightness();
  String page();
  String title();
  String artist();
  String notify();
  bool playing();
};

#endif
