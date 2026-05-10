#include <Arduino.h>
#include <time.h>
#include "constants.h"
#include "globals.h"
#include "clock.h"

Clock::Clock(MatrixPanel_I2S_DMA *display)
    : row(std::make_shared<std::vector<TextRow>>(
          std::initializer_list<TextRow>{
              TextRow(
                  {Text("00", Color{255, 0, 0}),
                   Text(":", Color{0, 255, 0}),
                   Text("00", Color{0, 0, 255})},
                  2)}))
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

    (*row)[0][0].setContent(hours);
    (*row)[0][2].setContent(minutes);
}

std::shared_ptr<std::vector<TextRow>> Clock::getText()
{
    return row;
}

void Clock::forceRerender()
{
}

void Clock::init()
{
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
