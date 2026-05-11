#ifndef SCROLLING_TEXT_ROW_H
#define SCROLLING_TEXT_ROW_H

#include "text.h"
#include "renderable-text.h"
#include <memory>

#include <Arduino.h>

class ScrollingTextRow : public RenderableText
{
private:
    bool dirtyFromScroll;
    std::shared_ptr<RenderableText> parent;
    int16_t scrollPosition;
    size_t scrollInterval;
    int16_t maxWidth;
    unsigned long nextFrame;
    int16_t getRenderedWidth();

public:
    ScrollingTextRow(std::shared_ptr<RenderableText> row, size_t scrollInterval, int16_t maxWidth);
    void tick();
    Text &operator[](size_t index);
    size_t fontSize();
    int16_t x();
    int16_t y();
    size_t size();
    String rowString() const;
    void markRendered();
    void setX(int16_t x);
    void setY(int16_t y);
    bool isDirty() const;
};
#endif