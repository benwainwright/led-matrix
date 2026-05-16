#include "text-row.h"

TextRow::TextRow(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::vector<Text> row)
    : TextRow(display, row, 1) {}
TextRow::TextRow(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::vector<Text> row,
                 size_t fontSize)
    : row(row), fontSizeValue(fontSize), xValue(0), yValue(0), display(display) {}

size_t TextRow::size() { return row.size(); }

int16_t TextRow::getRenderedWidth()

{

  if (display == nullptr) {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  String content = rowString();
  display->getTextBounds(content.c_str(), xValue, yValue, &x1, &y1, &w, &h);
  return w;
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
