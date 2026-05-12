#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "color.h"

class Text
{
private:
    String contentValue;
    Color colorValue;
    bool dirty;

public:
    Text(const String& content, Color color, size_t fontSize);
    Text(const String& content, Color color);
    void setContent(const String &content);
    String content() const;
    void setColor(Color color);
    Color color() const;
    bool isDirty() const;
    void markRendered();
};

#endif
