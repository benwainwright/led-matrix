#include "scrolling-text.h"
#include "calculator.h"

ScrollingText::ScrollingText(std::shared_ptr<RenderableText> parent, int scrollSpeed, int width)
    : RenderableText(parent), scrollSpeed(scrollSpeed), widthValue(width), scrollPosition(0), nextFrame(millis()),
      oldPositionValue(Coordinates{0, 0, 0, 0, 0, 0}), scrollPositionInitialized(false) {}

void ScrollingText::tick(MaskedDisplay* display) {
  auto now = millis();
  auto parentPosition = parent->position();
  auto contentWidth = parentPosition.width;
  auto viewportX = parentPosition.cursorX;

  if ((now - nextFrame) >= scrollSpeed) {
    if (contentWidth > widthValue) {
      display->setMask(parentPosition.cursorX, parentPosition.cursorY, widthValue, parentPosition.height);
      if (!scrollPositionInitialized) {
        scrollPosition = viewportX;
        scrollPositionInitialized = true;
      }
      if (now > nextFrame) {
        nextFrame += scrollSpeed;
        if (scrollPosition > viewportX - contentWidth) {
          scrollPosition -= 1;
        } else {
          scrollPosition = viewportX + widthValue;
        }
        setDirty();
      }
    } else {
      scrollPosition = viewportX;
      scrollPositionInitialized = true;
    }
    parent->tick(display);
  }
}

Coordinates ScrollingText::position() {
  auto position = parent->position();
  auto contentWidth = position.width;
  position.cursorX = contentWidth > widthValue ? scrollPosition : position.cursorX;
  position.width = widthValue;
  return position;
}

Coordinates ScrollingText::oldPosition() { return oldPositionValue; }

void ScrollingText::setPosition(Coordinates coords) {
  parent->setPosition(coords);
  if (!scrollPositionInitialized || coords.width <= widthValue) {
    scrollPosition = coords.cursorX;
    scrollPositionInitialized = true;
  }
}

void ScrollingText::markRendered() {
  this->oldPositionValue = this->position();
  parent->markRendered();
}
