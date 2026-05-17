#ifndef MASKED_DISPLAY_H
#define MASKED_DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <optional>

struct Rectangle {
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
};

class MaskedDisplay : public MatrixPanel_I2S_DMA {

private:
  std::optional<Rectangle> mask;
  bool pointIsInRectangle(int16_t x, int16_t y, Rectangle rect);

public:
  MaskedDisplay(HUB75_I2S_CFG config);

  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  void setMask(int16_t x, int16_t y, int16_t w, int16_t h);
  void clearMask();
};

#endif