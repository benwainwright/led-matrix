#ifndef RENDERABLE_TEXT_H
#define RENDERABLE_TEXT_H

#include <Arduino.h>
#include "text.h"

class RenderableText
{
public:
    virtual Text &operator[](size_t index) = 0;
    virtual size_t fontSize() = 0;
    virtual int16_t x() = 0;
    virtual int16_t y() = 0;
    virtual int16_t getRenderedWidth() = 0;
    virtual size_t size() = 0;
    virtual String rowString() const = 0;
    virtual void markRendered()
    {
    }
    virtual void tick()
    {
    }
    virtual void setX(int16_t x) = 0;
    virtual void setY(int16_t y) = 0;
    virtual bool isDirty() const = 0;
};
#endif