#include "clock.h"
#include <Arduino.h>
#include <time.h>

Clock::Clock()
    :

      row(std::initializer_list<std::shared_ptr<RenderableTextRow>>{std::make_shared<TextRow>(
          std::vector<std::shared_ptr<RenderableText>>{
              std::make_shared<Text>("00", Color{255, 255, 255}),
              std::make_shared<BlinkingText>(std::make_shared<Text>(":", Color{0, 100, 100}), Color{0, 51, 0}, 1000,
                                             1000),
              std::make_shared<Text>("00", Color{255, 255, 255})},
          CENTRE, 2)}) {}

String Clock::withLeadingZeros(int number) const {
  if (number < 10) {
    return "0" + String(number);
  }

  return String(number);
}

void Clock::tick() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  String hours = withLeadingZeros(timeinfo.tm_hour);
  String minutes = withLeadingZeros(timeinfo.tm_min);

  (*(row)[0])[0].setContent(hours);
  (*(row)[0])[2].setContent(minutes);
}

std::vector<std::shared_ptr<RenderableTextRow>> Clock::getText() { return row; }

void Clock::init() { configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); }
