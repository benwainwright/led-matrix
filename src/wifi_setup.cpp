#include "wifi_setup.h"
#include "app.h"
#include "constants.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <WiFi.h>

void setupMdns() {
  if (!MDNS.begin(HOSTNAME)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);
  }
}

void setupAPMode(App* app) {
  app->accessPointModeOn = true;
  Serial.println("WiFi details not configured. Access point mode enabled...");
  WiFi.softAP(AP_SSID);
  WiFi.softAPConfig(AP_IP, AP_IP, AP_NETMASK);
  Serial.print("AP IP address: ");
  Serial.println(AP_IP);
  app->dns.setErrorReplyCode(DNSReplyCode::NoError);
  app->dns.start(53, "*", AP_IP);
}

bool setupWifi(App* app) {
  vTaskDelay(pdMS_TO_TICKS(10));
  Serial.println();
  Serial.print("Connecting to ");

  auto ssid = app->config.getValue(WIFI_SSID_FIELD_NAME);
  auto password = app->config.getValue(WIFI_PASSWORD_FIELD_NAME);
  auto hostname = app->config.getValue(WEB_SERVER_HOST_NAME_FIELD_NAME);

  WiFi.setHostname(hostname.c_str());
  if (ssid == "" || password == "") {
    setupAPMode(app);
    setupMdns();
    return false;
  } else {
    WiFi.begin(ssid.c_str(), password.c_str());
    setupMdns();
  }

  unsigned long startedAt = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startedAt < 15000) {
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connection timed out");
    return true;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}