#include "globals.h"
#include "message.h"

void messageReceivedCallback(char *topic, byte *message, unsigned int length)
{
  vTaskDelay(pdMS_TO_TICKS(100));
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  state.brightness.receiveMqttMessage(topic, message, length);
}

void maintainMqttConnection()
{

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
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }
  client.loop();
}

void setupMqtt()
{
  client.setServer(mqttServer, 1883);
  client.setBufferSize(512);
  client.setCallback(messageReceivedCallback);
  maintainMqttConnection();
  state.brightness.initialise();
}
