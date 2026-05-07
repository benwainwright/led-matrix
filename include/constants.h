#ifndef CONSTANTS_H
#define CONSTANTS_H

#define LED_BUILTIN 2

#define R1_PIN 27
#define G1_PIN 14
#define B1_PIN 26
#define R2_PIN 25
#define G2_PIN 13
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

inline const char *ssid = "Ben's Flat (2.4Ghz)";
inline const char *password = "7ct3hqKA4y37";

inline const char *mqttUser = "screen";
inline const char *mqttPass = "5nW~Um_iqm56";
inline const char *mqttServer = "192.168.1.143";

inline const char *ntpServer = "pool.ntp.org";
inline constexpr long gmtOffset_sec = 0;
inline constexpr int daylightOffset_sec = 3600;

#define CLOCK_PAGE "clock"
#define DASHBOARD_PAGE "dashboard"

#endif
