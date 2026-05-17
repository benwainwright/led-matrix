#ifndef RENDERABLE_TEXT_H
#define RENDERABLE_TEXT_H

#include "text.h"
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class RenderableText {
public:
  virtual ~RenderableText() = default;
  virtual Text& operator[](size_t index) = 0;
  virtual size_t fontSize() = 0;
  virtual int16_t x() = 0;
  virtual int16_t y() = 0;
  virtual int16_t getRenderedWidth(MatrixPanel_I2S_DMA* display) = 0;
  virtual size_t size() = 0;
  virtual String rowString() const = 0;
  virtual void markRendered() {}
  virtual void tick(MatrixPanel_I2S_DMA* display) {}
  virtual void setX(int16_t x) = 0;
  virtual void setY(int16_t y) = 0;
  virtual bool isDirty() const = 0;
};
#endif