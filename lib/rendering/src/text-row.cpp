#include "text-row.h"
#include "calculator.h"
#include "pgm-read-glyph-ptr.h"
#include <Adafruit_GFX.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

TextRow::TextRow(std::vector<Text> row, Alignment alignment, size_t fontSize)
    : row(row), alignmentValue(alignment), fontSizeValue(fontSize), xValue(0), yValue(0) {}

size_t TextRow::size() { return row.size(); }

Alignment TextRow::alignment() { return this->alignmentValue; }

void TextRow::dirtyRow() {
  for (size_t i = 0; i < row.size(); i++) {
    row[i].setDirty();
  }
}

bool TextRow::isDirty() const {
  for (size_t i = 0; i < row.size(); i++) {
    if (row[i].isDirty()) {
      return true;
    }
  }
  return false;
}

void TextRow::setX(int16_t x) { xValue = x; }
void TextRow::setY(int16_t y) { yValue = y; }

int16_t TextRow::x() { return xValue; }

int TextRow::totalWidth() {
  int width = 0;
  for (int i = 0; i < row.size(); i++) {
    width += calculateWidth(row[i].content().c_str(), row[i].font(), fontSizeValue);
  }

  return width;
}

int16_t TextRow::y() { return yValue; }

Text& TextRow::operator[](size_t index) { return row[index]; }

String TextRow::rowString() const {
  String buffer;

  for (size_t i = 0; i < row.size(); i++) {
    buffer += row[i].content();
  }

  return buffer;
}

size_t TextRow::fontSize() { return fontSizeValue; }
