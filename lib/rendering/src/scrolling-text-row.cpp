
#include "scrolling-text-row.h"

ScrollingTextRow::ScrollingTextRow(std::shared_ptr<RenderableText> row, size_t scrollInterval,
                                   int16_t maxWidth)
    : parent(row), scrollInterval(scrollInterval), maxWidth(maxWidth), nextFrame(0),
      dirtyFromScroll(false), scrollPosition(0) {}

size_t ScrollingTextRow::size() { return parent->size(); }

bool ScrollingTextRow::isDirty() const { return dirtyFromScroll || parent->isDirty(); }

int16_t ScrollingTextRow::getRenderedWidth() { return parent->getRenderedWidth(); }

void ScrollingTextRow::setX(int16_t x) { parent->setX(x); }

void ScrollingTextRow::tick() {
  auto now = millis();
  auto renderedWidth = parent->getRenderedWidth();

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
  }
}

void ScrollingTextRow::markRendered() { dirtyFromScroll = false; }

void ScrollingTextRow::setY(int16_t y) { parent->setY(y); }

int16_t ScrollingTextRow::x() {
  if (parent->getRenderedWidth() > maxWidth) {
    return scrollPosition;
  } else {
    return parent->x();
  }
}

int16_t ScrollingTextRow::y() { return parent->y(); }

Text& ScrollingTextRow::operator[](size_t index) { return (*parent)[index]; }

String ScrollingTextRow::rowString() const { return parent->rowString(); }

size_t ScrollingTextRow::fontSize() { return parent->fontSize(); }
