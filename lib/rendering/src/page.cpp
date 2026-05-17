#include "page.h"
#include "calculator.h"

Page::Page(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::unique_ptr<Renderable> rows, const GFXfont* defaultFont,
           size_t gap)
    : pageDirty(true), rows(std::move(rows)), display(display), gap(gap), defaultFont(defaultFont) {}

void Page::setDirty() {
  auto text = rows->getText();
  for (size_t i = 0; i < text.size(); i++) {
    text[i]->dirtyRow();
  }
}

void Page::tick() { rows->tick(); }

void Page::init() { rows->init(); }

void Page::clear() { display->clearScreen(); }

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
  display->setTextWrap(false);
  auto text = rows->getText();
  for (size_t i = 0; i < text.size(); i++) {
    text[i]->tick(display.get());
  }
  if (isDirty()) {
    for (size_t i = 0; i < text.size(); i++) {
      updateRow(*text[i], i);
      renderRow(*text[i], i);
    }
  }
  pageDirty = false;
}

int16_t Page::getWidthOffsetForCentre(int16_t x, int16_t y, const char* message) {
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

int16_t Page::getHeightOffsetForCentre(int16_t x, int16_t y, const char* message, uint8_t index, uint8_t count) {
  if (display == nullptr) {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);

  int totalHeight = (h * count) + (gap * (count - 1));
  int startY = (display->height() - totalHeight) / 2;

  return startY + (index * (h + gap)) - y1;
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

void Page::positionRowContents(RenderableText& row, const GFXfont* defaultFont) {
  auto xPosition = row.x();
  for (int i = 0; i < row.size(); i++) {
    {

      int16_t x1;
      int16_t y1;
      uint16_t w;
      uint16_t h;

      Text& textItem = row[i];
      display->getTextBounds(textItem.content().c_str(), xPosition, row.y(), &x1, &y1, &w, &h);
      textItem.setPosition(Coordinates{x1, y1, h, w, xPosition, row.y()});

      xPosition += calculateWidth(textItem.content().c_str(), textItem.font(), row.fontSize());
    }
  }
}

void Page::clearText(Text& textItem, int size) {
  display->setTextSize(size);
  display->fillRect(textItem.oldPosition().x, textItem.oldPosition().y, textItem.oldPosition().width,
                    textItem.oldPosition().height, 0);
}

void Page::renderText(Text& textItem, int size) {
  if (!textItem.isDirty()) {
    return;
  }
  this->clearText(textItem, size);
  display->setCursor(textItem.position().cursorX, textItem.position().cursorY);
  display->setTextColor(display->color565(textItem.color().red, textItem.color().green, textItem.color().blue));
  display->print(textItem.content());
  textItem.markRendered();
}

void Page::updateRow(RenderableText& row, uint8_t index) {
  auto text = rows->getText();
  for (size_t i = 0; i < row.size(); i++) {
    row[i].setDefaultFont(defaultFont);
  }
  row.tick(display.get());

  display->setTextSize(row.fontSize());
  if (row.alignment() == CENTRE) {
    auto raw = row.rowString();
    auto widthOffset = getWidthOffsetForCentre(row.x(), row.y(), raw.c_str());
    auto heightOffset = getHeightOffsetForCentre(row.x(), row.y(), raw.c_str(), index, text.size());
    row.setX(widthOffset);
    row.setY(heightOffset);
  }
  this->positionRowContents(row, defaultFont);
}

void Page::renderRow(RenderableText& row, uint8_t index) {

  for (size_t i = 0; i < row.size(); i++) {
    if (row[i].isDirty()) {
      this->renderText(row[i], row.fontSize());
    }
  }
  row.markRendered();
}
