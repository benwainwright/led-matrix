#ifndef TEXT_ROW_H
#define TEXT_ROW_H
#include "alignment.h"
#include "renderable-text-row.h"
#include "text.h"
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class TextRow : public RenderableTextRow {
private:
  std::vector<Text> row;
  Alignment alignmentValue;
  size_t fontSizeValue;
  int16_t xValue;
  int16_t yValue;

public:
  TextRow(std::vector<Text> row, Alignment alignment = LEFT, size_t fontSize = 1);
  int16_t x();
  Alignment alignment();
  int16_t y();
  void setX(int16_t x);
  void setY(int16_t y);
  size_t size();
  size_t fontSize();
  void tick();
  int totalWidth();
  void dirtyRow();
  bool isDirty() const;
  String rowString() const;
  Text& operator[](size_t index);
};
#endif
