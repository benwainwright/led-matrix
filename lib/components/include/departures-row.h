#ifndef DEPARTURE_ROW_H
#define DEPARTURE_ROW_H
#include <Rendering.h>
#include <rtt.h>

class DepartureRow {
private:
  std::shared_ptr<RenderableText> text;
  Departure departure;
  String withLeadingZeros(int number) const;
  std::string toTime(time_t time) const;

public:
  DepartureRow(size_t displayWidth);
  void setContent(Departure departure);
  std::shared_ptr<RenderableText> getText();
};
#endif