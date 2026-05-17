#include "masked-display.h"

MaskedDisplay::MaskedDisplay(HUB75_I2S_CFG config) : MatrixPanel_I2S_DMA(config), mask({}) {}

bool MaskedDisplay::pointIsInRectangle(int16_t x, int16_t y, Rectangle rect) {
  return x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h;
}

void MaskedDisplay::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (!mask.has_value() || pointIsInRectangle(x, y, mask.value())) {
    MatrixPanel_I2S_DMA::drawPixel(x, y, color);
  }
}

void MaskedDisplay::setMask(int16_t x, int16_t y, int16_t w, int16_t h) { this->mask = Rectangle{x, y, w, h}; }

void MaskedDisplay::clearMask() { mask = {}; }
