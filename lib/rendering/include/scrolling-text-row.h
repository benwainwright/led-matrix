#ifndef SCROLLING_TEXT_ROW_H
#define SCROLLING_TEXT_ROW_H

#include "alignment.h"
#include "renderable-text-row.h"
#include "text.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <memory>

class ScrollingTextRow : public RenderableTextRow {
private:
  std::shared_ptr<RenderableTextRow> parent;
  size_t scrollInterval;
  int16_t maxWidth;
  unsigned long nextFrame;
  bool dirtyFromScroll;
  int16_t scrollPosition;

public:
  ScrollingTextRow(std::shared_ptr<RenderableTextRow> row, size_t scrollInterval, int16_t maxWidth);
  void tick(MatrixPanel_I2S_DMA* display) override;
  Text& operator[](size_t index);
  void dirtyRow();
  size_t fontSize();
  int16_t x();
  int16_t y();
  size_t size();
  Alignment alignment();
  int totalWidth();
  String rowString() const;
  void markRendered();
  void setX(int16_t x);
  void setY(int16_t y);
  bool isDirty() const;
};
#endif