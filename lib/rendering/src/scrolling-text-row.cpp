
#include "scrolling-text-row.h"
#include "calculator.h"
#include <string>

ScrollingTextRow::ScrollingTextRow(std::shared_ptr<RenderableText> row, size_t scrollInterval, int16_t maxWidth)
    : parent(row), scrollInterval(scrollInterval), maxWidth(maxWidth), nextFrame(0), dirtyFromScroll(false),
      scrollPosition(0) {}

size_t ScrollingTextRow::size() { return parent->size(); }

Alignment ScrollingTextRow::alignment() { return parent->alignment(); }

bool ScrollingTextRow::isDirty() const { return dirtyFromScroll || parent->isDirty(); }

void ScrollingTextRow::setX(int16_t x) { parent->setX(x); }

void ScrollingTextRow::tick(MatrixPanel_I2S_DMA* display) {
  auto now = millis();
  auto renderedWidth = getRenderedWidth(*display, rowString().c_str(), parent->x(), parent->y());

  if (renderedWidth > maxWidth) {
    if (now > nextFrame) {
      nextFrame = now + scrollInterval;
      if (scrollPosition > -renderedWidth) {
        scrollPosition -= 1;
      } else {
        scrollPosition = maxWidth;
      }
      dirtyFromScroll = true;
    }
  } else {
    scrollPosition = parent->x();
  }

  Serial.printf("scrollpos: %d\n", scrollPosition);
}

void ScrollingTextRow::markRendered() { dirtyFromScroll = false; }

int ScrollingTextRow::totalWidth() { return parent->totalWidth(); }

void ScrollingTextRow::setY(int16_t y) { parent->setY(y); }

int16_t ScrollingTextRow::x() {
  auto width = parent->totalWidth();
  if (width > maxWidth) {
    return scrollPosition;
  }
  return parent->x();
}

int16_t ScrollingTextRow::y() { return parent->y(); }

Text& ScrollingTextRow::operator[](size_t index) { return (*parent)[index]; }

String ScrollingTextRow::rowString() const { return parent->rowString(); }

size_t ScrollingTextRow::fontSize() { return parent->fontSize(); }

void ScrollingTextRow::dirtyRow() { return parent->dirtyRow(); }