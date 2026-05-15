#include "run_mqtt.h"
#include <Arduino.h>

void maintainMqttConnection(App *app) {
  bool connectedThisCall = false;

  if (!app->mqtt.connected()) {
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  while (!app->mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (app->mqtt.connect("ESP8266Client", mqttUser, mqttPass)) {
      Serial.println("connected");
      connectedThisCall = true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(app->mqtt.state());
      Serial.println(" try again in 5 seconds");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }

  if (connectedThisCall) {
    app->state.initialise();
  }

  app->mqtt.loop();
}

void setupMqtt(App *app) {
  app->mqtt.setServer(mqttServer, 1883);
  app->mqtt.setBufferSize(1024);
  app->mqtt.setCallback([app](char *topic, byte *message, unsigned int length) {
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.println();
    app->state.receiveMqttMessage(topic, message, length);
  });
  maintainMqttConnection(app);
}
