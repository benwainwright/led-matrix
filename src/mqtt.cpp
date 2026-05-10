#include "globals.h"

void messageReceivedCallback(char *topic, byte *message, unsigned int length)
{
  vTaskDelay(pdMS_TO_TICKS(100));
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.println();
  state.receiveMqttMessage(topic, message, length);
}

void maintainMqttConnection()
{
  bool connectedThisCall = false;

  if (!client.connected())
  {
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqttUser, mqttPass))
    {
      Serial.println("connected");
      connectedThisCall = true;
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }

  if (connectedThisCall)
  {
    state.initialise();
  }

  client.loop();
}

void setupMqtt()
{
  client.setServer(mqttServer, 1883);
  client.setBufferSize(1024);
  client.setCallback(messageReceivedCallback);
  maintainMqttConnection();
}
