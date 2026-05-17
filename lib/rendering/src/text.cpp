#include "text.h"
#include "calculator.h"
#include "coordinates.h"
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

Text::Text(const String& content, Color color, const GFXfont* font, int fontSize)
    : oldPositionValue(Coordinates{0, 0, 0, 0, 0, 0}), positionValue(Coordinates{0, 0, 0, 0, 0, 0}), fontValue(font),
      defaultFont(nullptr), contentValue(content), colorValue(color), dirty(true), fontSizeValue(fontSize) {}

void Text::setColor(Color color) {
  if (color.red != colorValue.red || color.green != colorValue.green || color.blue != colorValue.blue) {
    dirty = true;
  }
  colorValue = color;
}

int Text::getFontSize() { return fontSizeValue; }

Coordinates Text::oldPosition() { return oldPositionValue; }

Coordinates Text::position() { return positionValue; }

void Text::setPosition(Coordinates coords) {

  if (coords.cursorX != this->positionValue.cursorX || coords.cursorY != this->positionValue.cursorY ||
      coords.x != this->positionValue.x || coords.y != this->positionValue.y ||
      coords.width != this->positionValue.width || coords.height != this->positionValue.height) {
    dirty = true;
    oldPositionValue = positionValue;
    positionValue = coords;
  }
}

const GFXfont* Text::font() { return this->fontValue != nullptr ? this->fontValue : this->defaultFont; }

void Text::setDirty() { dirty = true; }

void Text::setDefaultFont(const GFXfont* font) { defaultFont = font; }

void Text::setContent(const String& content) {
  if (contentValue != content) {
    this->oldPositionValue = this->positionValue;
    contentValue = content;
    dirty = true;
  }
}

Color Text::color() const { return colorValue; }

const String& Text::content() const { return contentValue; }

bool Text::isDirty() const { return dirty; }

void Text::markRendered() {
  dirty = false;
  this->oldPositionValue = this->positionValue;
}
