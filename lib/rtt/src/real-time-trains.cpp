#include "real-time-trains.h"
#include "expected.h"
#include "parse-iso-date.h"
#include <map>

RealTimeTrains::RealTimeTrains(const std::string& refreshToken)
    : client("https://data.rtt.io", refreshToken) {};

tl::expected<std::vector<Departure>, ErrorResponse>
RealTimeTrains::departuresFrom(const std::string& station) {

  auto response =
      client.get("/gb-nr/location", std::map<std::string, std::string>{{"code", station},
                                                                       {"timeTolerance", "false"},
                                                                       {"detailed", "false"},
                                                                       {"stpFilter", "WVS"}});

  if (response.has_value()) {

    Serial.println("Response had a value");
    JsonArray services = response.value()["services"].as<JsonArray>();

    std::vector<Departure> departures;
    for (auto service : services) {
      if (service["temporalData"].containsKey("departure")) {

        auto departure = service["temporalData"]["departure"];
        auto scheduled = departure["scheduleAdvertised"] | departure["scheduleInternal"];
        auto realtime = departure["realtimeForecast"] | departure["realtimeActual"] | scheduled;
        auto cancelled = departure["isCancelled"].as<bool>();

        auto location = service["locationMetadata"];
        auto plannedPlatform = location["platform"]["planned"].as<int>();
        auto forcastedPlatform = location["platform"]["forecast"].as<int>();

        auto origin = service["origin"].as<JsonArray>()[0]["location"]["description"];
        auto destination = service["destination"].as<JsonArray>()[0]["location"]["description"];

        departures.push_back(Departure{parseIso8601(scheduled), parseIso8601(realtime), cancelled,
                                       plannedPlatform, forcastedPlatform, origin, destination});
      }
    }

    return departures;
  } else {
    return tl::unexpected(response.error());
  }
}
