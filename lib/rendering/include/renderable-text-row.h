#ifndef RENDERABLE_TEXT_ROW_H
#define RENDERABLE_TEXT_ROW_H

#include "alignment.h"
#include "masked-display.h"
#include "renderable-text.h"
#include <Arduino.h>

class RenderableTextRow {
public:
  virtual ~RenderableTextRow() = default;
  virtual RenderableText& operator[](size_t index) = 0;
  virtual size_t fontSize() = 0;
  virtual Alignment alignment() = 0;
  virtual int16_t x() = 0;
  virtual void setDefaultFont(const GFXfont* font) = 0;
  virtual int16_t y() = 0;
  virtual size_t size() = 0;
  virtual String rowString() const = 0;
  virtual void markRendered() {}
  virtual int totalWidth() = 0;
  virtual void dirtyRow() = 0;
  virtual void tick(MaskedDisplay* display) {}
  virtual void setX(int16_t x) = 0;
  virtual void setY(int16_t y) = 0;
  virtual bool isDirty() const = 0;
};
#endif