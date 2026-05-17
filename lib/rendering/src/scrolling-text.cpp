#include "scrolling-text.h"
#include "calculator.h"

ScrollingText::ScrollingText(int scrollSpeed, int width)
    : scrollSpeed(scrollSpeed), width(width), scrollPosition(0), nextFrame(millis()),
      oldPositionValue(Coordinates{0, 0, 0, 0, 0, 0}) {}

void ScrollingText::tick() {
  auto now = millis();
  auto contentWidth = calculateWidth(parent->content().c_str(), parent->font(), parent->getFontSize());

  if ((now - nextFrame) >= scrollSpeed) {
    if (contentWidth > width) {
      if (now > nextFrame) {
        nextFrame += scrollSpeed;
        if (scrollPosition > -contentWidth) {
          scrollPosition -= 1;
        } else {
          scrollPosition = width;
        }
        setDirty();
      }
    } else {
      scrollPosition = parent->position().cursorX;
    }
    parent->tick();
  }
}

Coordinates ScrollingText::position() {
  auto position = parent->position();
  auto contentWidth = calculateWidth(parent->content().c_str(), parent->font(), parent->getFontSize());
  position.x = contentWidth > width ? scrollPosition : position.x;
  oldPositionValue = position;
  return position;
}

Coordinates ScrollingText::oldPosition() { return oldPositionValue; }

void ScrollingText::markRendered() {
  this->oldPositionValue = this->position();
  parent->markRendered();
}
