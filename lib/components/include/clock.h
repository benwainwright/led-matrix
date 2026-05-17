#ifndef CLOCK_H
#define CLOCK_H

#define NOT_SET -1

#include "renderable.h"
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

inline const char* ntpServer = "pool.ntp.org";
inline constexpr long gmtOffset_sec = 0;
inline constexpr int daylightOffset_sec = 3600;

class Clock : public Renderable {

private:
  String withLeadingZeros(int number) const;
  std::vector<std::shared_ptr<RenderableTextRow>> row;

public:
  Clock();
  void tick() override;
  void init() override;
  Text& operator[](size_t index);
  std::vector<std::shared_ptr<RenderableTextRow>> getText() override;
};

#endif
