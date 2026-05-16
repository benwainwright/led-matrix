#ifndef CLOCK_H
#define CLOCK_H

#define NOT_SET -1

#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

inline const char* ntpServer = "pool.ntp.org";
inline constexpr long gmtOffset_sec = 0;
inline constexpr int daylightOffset_sec = 3600;

class Clock {

private:
  String withLeadingZeros(int number) const;
  std::vector<std::shared_ptr<RenderableText>> row;

public:
  Clock(std::shared_ptr<MatrixPanel_I2S_DMA> display);

  void tick();
  void init();
  Text& operator[](size_t index);
  std::vector<std::shared_ptr<RenderableText>> getText();
};

#endif
