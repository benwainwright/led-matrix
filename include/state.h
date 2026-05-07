#include "Arduino.h"
#include "number-mqtt-entity.h"
#include "select-mqtt-entity.h"
#include "constants.h"
#include "mqtt-device.h"

class State
{

private:
    MqttDevice device;
    NumberMqttEntity brightnessControl;
    SelectMqttEntity pageSelector;

public:
    State(PubSubClient *initClient);
    void initialise();
    void receiveMqttMessage(char *topic, byte *message, unsigned int length);
    u_int8_t brightness();
    String page();
};