#include "run_mqtt.h"
#include <Arduino.h>

void maintainMqttConnection(App* app) {
  bool connectedThisCall = false;

  auto mqttUser = app->config.getValue(MQTT_USER_FIELD_NAME);
  auto mqttPass = app->config.getValue(MQTT_PASS_FIELD_NAME);
  auto mqttHost = app->config.getValue(MQTT_SERVER_FIELD_NAME);

  if (mqttUser == "" || mqttPass == "" || mqttHost == "") {
    Serial.println("Mqtt details not configured");
    vTaskDelay(pdMS_TO_TICKS(100));
    return;
  }

  if (!app->mqtt.connected()) {
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  while (!app->mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (app->mqtt.connect("ESP8266Client", mqttUser.c_str(), mqttPass.c_str())) {
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

void setupMqtt(App* app) {
  auto host = app->config.getValue(MQTT_SERVER_FIELD_NAME);
  Serial.printf("MQTT Server set to %s\n", host.c_str());
  app->mqtt.setServer(host.c_str(), 1883);
  app->mqtt.setBufferSize(1024);
  app->mqtt.setCallback([app](char* topic, byte* message, unsigned int length) {
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.println();
    app->state.receiveMqttMessage(topic, message, length);
  });
  maintainMqttConnection(app);
}
