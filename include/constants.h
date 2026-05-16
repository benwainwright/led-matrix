#ifndef CONSTANTS_H
#define CONSTANTS_H

#define LED_BUILTIN 2

#define G1_PIN 14
#define G2_PIN 13
#define B1_PIN 26

#define R1_PIN 27
#define R2_PIN 25
#define B2_PIN 33
#define A_PIN 23
#define B_PIN 16
#define C_PIN 22
#define D_PIN 17
#define E_PIN -1
#define LAT_PIN 18
#define OE_PIN 19
#define CLK_PIN 21

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

#define HOSTNAME "bedroom-screen"

#define WIFI_SSID_FIELD_NAME "wifi-ssid"
#define WIFI_PASSWORD_FIELD_NAME "wifi-password"
#define MQTT_USER_FIELD_NAME "mqtt-user"
#define MQTT_PASS_FIELD_NAME "mqtt-pass"
#define MQTT_SERVER_FIELD_NAME "mqtt-server"
#define WEB_SERVER_HOST_NAME_FIELD_NAME "server-host"
#define RTT_TOKEN_FIELD_NAME "rtt-trains"
#define RTT_STATION_CODE_FIELD_NAME "rtt-station"
#define ARTISTS_TOPIC_FIELD_NAME "artist-topic"
#define TITLE_TOPIC_FIELD_NAME "title-topic"
#define STATUS_TOPIC_FIELD_NAME "status-topic"
#define AP_SSID "led-screen-ap"

#define WIFI_SCAN_INTERVAL_SECONDS 30
#define SKIPPED_SCAN -1
#define SCAN_RUNNING -2

#define CLOCK_PAGE "clock"
#define MEDIA_PAGE "media"
#define TRAINS_PAGE "trains"

#endif
