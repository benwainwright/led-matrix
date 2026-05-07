#include <Arduino.h>
#include <time.h>
#include "constants.h"
#include "message.h"
#include "globals.h"
#include "clock.h"

Clock::Clock(
    MatrixPanel_I2S_DMA *display) : message(display, 2, X_CENTRED, Y_CENTRED)
{
}

String Clock::withLeadingZeros(int number)
{
    if (number < 10)
    {
        return "0" + String(number);
    }

    return String(number);
}

void Clock::tick()
{
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    String hours = withLeadingZeros(timeinfo.tm_hour);
    String minutes = withLeadingZeros(timeinfo.tm_min);
    String time = hours + ":" + minutes;

    if (time != previousTime)
    {
        previousTime = time;
        message.write(time);
    }
}

void Clock::forceRerender()
{
    message.force();
}

void Clock::init()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
