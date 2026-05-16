#ifndef DEPARTURE_H
#define DEPARTURE_H

#include <string>
#include <time.h>

struct Departure {
  time_t scheduledDeparture;
  time_t realtimeDeparture;
  bool cancelled;
  int plannedPlatform;
  int forcastedPlatform;
  std::string from;
  std::string to;
};

#endif