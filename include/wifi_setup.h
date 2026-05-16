#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include "app.h"
#include <DNSServer.h>
#include <WiFi.h>

void setupConfigServer(App* app);
bool setupWifi(App* app);
long hydrateFields(Form& form, long lastWifiScan);

inline const IPAddress AP_IP = IPAddress(192, 168, 4, 1);
inline const IPAddress AP_NETMASK = IPAddress(255, 255, 255, 0);

#endif
