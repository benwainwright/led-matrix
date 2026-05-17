#ifndef SCROLLING_TEXT_H
#define SCROLLING_TEXT_H

#include "renderable-text.h"

class ScrollingText : public RenderableText {
private:
  int scrollSpeed;
  int width;
  int scrollPosition;
  unsigned long nextFrame;
  Coordinates oldPositionValue;

public:
  void tick() override;

  ScrollingText(int scrollSpeed, int width);
  Coordinates oldPosition() override;
  Coordinates position() override;
  void markRendered() override;
};

#endif