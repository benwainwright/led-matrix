#include "app.h"
#include <exception>
#include <rtt.h>

static constexpr TickType_t TRAIN_REFRESH_INTERVAL = pdMS_TO_TICKS(60000);

void runTrainLoop(void* parameter) {
  App* app = static_cast<App*>(parameter);

  xEventGroupWaitBits(app->finishedDataInitialisationEventGroup, DATA_READY_BIT, pdFALSE, pdFALSE,
                      portMAX_DELAY);

  auto token = app->config.getValue(RTT_TOKEN_FIELD_NAME);
  auto station = app->config.getValue(RTT_STATION_CODE_FIELD_NAME);

  if (token == "") {
    Serial.println("No RTT token found. Killing RTT task...");
    vTaskDelete(nullptr);
  }

  if (station == "") {
    Serial.println("No station code found. Killing RTT task...");
    vTaskDelete(nullptr);
  }

  auto trainsClient = RealTimeTrains(token);

  while (true) {
    auto departures = trainsClient.departuresFrom(station);
    if (!departures.has_value()) {
      Serial.println("Request failed");
      Serial.printf("Status code: %d\n", departures.error().statusCode);
      Serial.printf("Body: %s\n", departures.error().responseBody.c_str());
    } else {
      app->departures = departures.value();
    }

    vTaskDelay(TRAIN_REFRESH_INTERVAL);
  }
}
