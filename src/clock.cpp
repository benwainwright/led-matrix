#include <Arduino.h>
#include <time.h>
#include "constants.h"
#include "message.h"
#include "globals.h"

void initTime()
{
    Serial.println();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

String withLeadingZeros(int number)
{
    if (number < 10)
    {
        return "0" + String(number);
    }

    return String(number);
}

void renderClock()
{
    Message message(display.get(), 2, X_CENTRED, Y_CENTRED);
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    String hours = withLeadingZeros(timeinfo.tm_hour);
    String minutes = withLeadingZeros(timeinfo.tm_min);
    String time = hours + ":" + minutes;

    message.write(time);
}