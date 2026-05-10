#include <Arduino.h>>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "rendering/text.h"

Text::Text(String content, Color color) : contentValue(content), colorValue(color), dirty(true) {}

void Text::setColor(Color color)
{
    if (color.red != colorValue.red || color.green != colorValue.green || color.blue != colorValue.blue)
    {
        dirty = true;
    }
    colorValue = color;
}

void Text::setContent(String content)
{
    if (contentValue != content)
    {
        dirty = true;
    }
    contentValue = content;
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
