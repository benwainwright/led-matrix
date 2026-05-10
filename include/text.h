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
    Text(String content, Color color);
    void setContent(String content);
    String content() const;
    void setColor(Color color);
    Color color() const;
    bool isDirty() const;
    void markRendered();
};

#endif
