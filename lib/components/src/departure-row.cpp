#include "departures-row.h"
#include "scrolling-text-row.h"
#include <memory>
#include <string>
#include <time.h>

DepartureRow::DepartureRow(size_t displayWidth)
    : text(std::make_shared<TextRow>(
          std::vector<std::shared_ptr<RenderableText>>{
              std::make_shared<Text>("00:00", Color{168, 130, 221}), std::make_shared<Text>(" ", Color{255, 255, 255}),
              std::make_shared<Text>("14", Color{224, 141, 121}), std::make_shared<Text>(" ", Color{255, 255, 255}),
              std::make_shared<Text>("Station", Color{179, 242, 221})},
          LEFT)) {}

String DepartureRow::withLeadingZeros(int number) const {
  if (number < 10) {
    return "0" + String(number);
  }

  return String(number);
}

std::string DepartureRow::toTime(time_t time) const {
  char buff[20];
  strftime(buff, 20, "%H:%M", localtime(&time));
  return std::string(buff);
}

void DepartureRow::setContent(Departure departure) {
  (*text)[0].setContent(toTime(departure.scheduledDeparture).c_str());
  (*text)[2].setContent(departure.to.c_str());
  std::string platformString = "Platform " + std::to_string(departure.plannedPlatform);
  (*text)[4].setContent(platformString.c_str());
}
std::shared_ptr<RenderableTextRow> DepartureRow::getText() { return text; }