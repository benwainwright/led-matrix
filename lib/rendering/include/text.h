#ifndef TEXT_FUNC_H
#define TEXT_FUNC_H

#include "color.h"
#include <Arduino.h>

class Text {
private:
  String contentValue;
  Color colorValue;
  bool dirty;

public:
  Text(const String& content, Color color);
  void setContent(const String& content);
  const String& content() const;
  void setColor(Color color);
  Color color() const;
  bool isDirty() const;
  void markRendered();
};

#endif
