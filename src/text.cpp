#include <Arduino.h>>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "text.h"

Text::Text(String content, Color color) : contentValue(content), colorValue(color), dirty(true) {}

void Text::setColor(Color color)
{
    colorValue = color;
    dirty = true;
}

void Text::setContent(String content)
{
    contentValue = content;
    dirty = true;
}

Color Text::color() const
{
    return colorValue;
}

String Text::content() const
{
    return contentValue;
}

bool Text::isDirty() const
{
    return dirty;
}

void Text::markRendered()
{
    dirty = false;
}
