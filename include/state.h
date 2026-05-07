#include <ctime>
#include "mqtt-entity.h"

enum Page
{
    CLOCK
};

struct ScreenState
{
    time_t time;
    Page page;
    MqttEntity brightness;
};