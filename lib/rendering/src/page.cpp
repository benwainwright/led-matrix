#include "page.h"

Page::Page(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::unique_ptr<Renderable> rows)
    : Page::Page(display, std::move(rows), 1) {}

Page::Page(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::unique_ptr<Renderable> rows,
           size_t gap)
    : pageDirty(true), rows(std::move(rows)), display(display), gap(gap) {}

void Page::setDirty() { pageDirty = true; }

void Page::tick() { rows->tick(); }
void Page::init() { rows->init(); }

bool Page::isDirty() {
  if (pageDirty) {
    return true;
  }

  auto text = rows->getText();

  for (size_t i = 0; i < text.size(); i++) {
    if (text[i]->isDirty()) {
      return true;
    }
  }

  return false;
}

void Page::render() {
  auto text = rows->getText();
  for (size_t i = 0; i < text.size(); i++) {
    text[i]->tick(display.get());
  }
  if (isDirty()) {
    display->clearScreen();
    for (size_t i = 0; i < text.size(); i++) {
      positionRow(*text[i], i);
      renderRow(*text[i], i);
    }
  }
  pageDirty = false;
}

int16_t Page::getWidthOffsetForCentre(const char* message) {
  if (display == nullptr) {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  return ((display->width() - w) / 2) - x1;
}

int16_t Page::getHeightOffsetForCentre(const char* message, uint8_t index, uint8_t count) {
  if (display == nullptr) {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  float centreY = (display->height() - (h + gap)) / 2.0f - y1;
  float rowOffset = (index - ((count - 1) / 2.0f)) * (h + gap);

  return centreY + rowOffset;
}

int16_t Page::getWidthOfTextItem(const Text& text, int16_t x, int16_t y) {

  if (display == nullptr) {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  String content = text.content();
  display->getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
  return w;
}

void Page::positionRow(RenderableText& row, uint8_t index) {
  auto text = rows->getText();
  auto raw = row.rowString();
  display->setTextSize(row.fontSize());
  display->setTextWrap(false);
  auto widthOffset = getWidthOffsetForCentre(raw.c_str());
  auto heightOffset = getHeightOffsetForCentre(raw.c_str(), index, text.size());

  row.setX(widthOffset);
  row.setY(heightOffset);
}

void Page::renderRow(RenderableText& row, uint8_t index) {
  display->setCursor(row.x(), row.y());

  for (size_t i = 0; i < row.size(); i++) {

    display->setTextColor(
        display->color565(row[i].color().red, row[i].color().green, row[i].color().blue));

    display->print(row[i].content());

    row[i].markRendered();
  }

  row.markRendered();
}
