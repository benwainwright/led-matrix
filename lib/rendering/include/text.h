#ifndef TEXT_FUNC_H
#define TEXT_FUNC_H

#include "alignment.h"
#include "color.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <optional>

struct Coordinates {
  int x;
  int y;
  int height;
  int width;
  int cursorX;
  int cursorY;
};

class Text {
private:
  Coordinates oldPositionValue;
  Coordinates positionValue;
  const GFXfont* fontValue;
  const GFXfont* defaultFont;
  String contentValue;
  Color colorValue;
  bool dirty;

public:
  Text(const String& content, Color color, const GFXfont* font = nullptr);
  void setContent(const String& content);
  const String& content() const;
  void setColor(Color color);
  Color color() const;
  void setDefaultFont(const GFXfont* font);
  void setDirty();
  Coordinates oldPosition();
  Coordinates position();
  void setPosition(Coordinates coords);
  const GFXfont* font();
  bool isDirty() const;
  void markRendered();
};

#endif
