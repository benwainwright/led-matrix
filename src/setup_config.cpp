#include "setup_config.h"
#include "app.h"
#include "constants.h"
#include <Arduino.h>
#include <Config.h>
#include <WiFi.h>

long hydratreWifiOptions(SelectField& selectField, long lastScan) {
  long now = millis();

  if (lastScan != 0 && now < (lastScan + WIFI_SCAN_INTERVAL_SECONDS * 1000)) {
    return SKIPPED_SCAN;
  }
  int16_t status = WiFi.scanComplete();

  Serial.printf("status: %d\n", status);

  if (status == WIFI_SCAN_RUNNING) {
    return SCAN_RUNNING;
  }

  if (status > 0) {
    Serial.println("WiFi scan finished");
    int numberOfNetworks = status;
    std::vector<SelectOption> wifiNetworks;
    if (selectField.value() == "") {
      wifiNetworks.push_back(SelectOption{"", ""});
    }
    if (numberOfNetworks == 0) {
      Serial.println("No WIFI networks found");
    } else {
      for (int i = 0; i < numberOfNetworks; i++) {
        wifiNetworks.push_back(SelectOption{WiFi.SSID(i).c_str(), WiFi.SSID(i).c_str()});
      }
    }
    selectField.setOptions(std::move(wifiNetworks));
    WiFi.scanDelete();
    return now;
  }

  if (status == WIFI_SCAN_FAILED) {
    Serial.println("WiFi scan failed. Restarting");
  }

  Serial.println("Starting WiFi scan");
  WiFi.scanNetworks(true);
  return SCAN_RUNNING;
}

void setupConfigServer(App* app) {
  auto form = std::make_unique<Form>();
  std::vector<std::unique_ptr<Field>> fields;
  auto ssidSelect =
      std::make_unique<SelectField>(WIFI_SSID_FIELD_NAME, "Wifi SSID", std::vector<SelectOption>{},
                                    "", [lastScan = long{0}](SelectField& field) mutable {
                                      auto scanStatus = hydratreWifiOptions(field, lastScan);
                                      if (scanStatus > 0) {
                                        lastScan = scanStatus;
                                      }
                                    });
  fields.push_back(std::move(ssidSelect));
  fields.push_back(
      std::make_unique<TextField>(WIFI_PASSWORD_FIELD_NAME, "Wifi Password", "password"));
  fields.push_back(std::make_unique<TextField>(MQTT_USER_FIELD_NAME, "MQTT Username"));
  fields.push_back(std::make_unique<TextField>(MQTT_PASS_FIELD_NAME, "MQTT Password", "password"));
  fields.push_back(std::make_unique<TextField>(MQTT_SERVER_FIELD_NAME, "MQTT Host"));
  fields.push_back(std::make_unique<TextField>(WEB_SERVER_HOST_NAME_FIELD_NAME, "Hostname", "text",
                                               "bedroom-screen"));
  form->setFields(std::move(fields));
  app->config.setForm(std::move(form));
}
