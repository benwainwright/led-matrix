#ifndef TEXT_FUNC_H
#define TEXT_FUNC_H

#include "alignment.h"
#include "color.h"
#include "renderable-text.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <optional>

class Text : public RenderableText {
private:
  Coordinates oldPositionValue;
  Coordinates positionValue;
  const GFXfont* fontValue;
  const GFXfont* defaultFont;
  String contentValue;
  Color colorValue;
  bool dirty;
  size_t fontSizeValue;

public:
  Text(const String& content, Color color, const GFXfont* font = nullptr, int fontSize = 1);
  void setContent(const String& content) override;
  const String& content() const override;
  void setColor(Color color) override;
  Color color() const override;
  void setDefaultFont(const GFXfont* font) override;
  void setDirty() override;
  int getFontSize() override;
  Coordinates oldPosition() override;
  Coordinates position() override;
  void setPosition(Coordinates coords) override;
  const GFXfont* font() override;
  bool isDirty() const override;
  void markRendered() override;
};

#endif
