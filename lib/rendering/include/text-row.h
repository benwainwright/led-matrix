#ifndef TEXT_ROW_H
#define TEXT_ROW_H
#include "renderable-text.h"
#include "text.h"
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class TextRow : public RenderableText {
private:
  std::vector<Text> row;
  size_t fontSizeValue;
  int16_t xValue;
  int16_t yValue;
  int16_t getRenderedWidth(MatrixPanel_I2S_DMA* display);

public:
  TextRow(std::vector<Text> row);
  TextRow(std::vector<Text> row, size_t fontSize);
  int16_t x();
  int16_t y();
  void setX(int16_t x);
  void setY(int16_t y);
  size_t size();
  size_t fontSize();
  bool isDirty() const;
  String rowString() const;
  Text& operator[](size_t index);
};
#endif
