#include "departures-row.h"
#include "scrolling-text-row.h"
#include <string>
#include <time.h>

DepartureRow::DepartureRow(size_t displayWidth)
    : text(std::make_shared<ScrollingTextRow>(
          std::make_shared<TextRow>(
              std::vector<Text>{Text("00:00", Color{168, 130, 221}), Text(" ", Color{255, 255, 255}),
                                Text("Station", Color{224, 141, 121}), Text(" ", Color{255, 255, 255}),
                                Text("14", Color{179, 242, 221})},
              CENTRE),
          50, displayWidth)) {}

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
std::shared_ptr<RenderableText> DepartureRow::getText() { return text; }