#ifndef REAL_TIME_TRAINS_H
#define REAL_TIME_TRAINS_H
#include "departure.h"
#include "error-response.h"
#include "expected.h"
#include "request-client.h"
#include <vector>
class RealTimeTrains {

private:
  RequestClient client;

public:
  RealTimeTrains(const std::string& refreshToken);

  tl::expected<std::vector<Departure>, ErrorResponse> departuresFrom(const std::string& station);
};
#endif