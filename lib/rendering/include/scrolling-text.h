#ifndef SCROLLING_TEXT_H
#define SCROLLING_TEXT_H

#include "renderable-text.h"

class ScrollingText : public RenderableText {
private:
  int scrollSpeed;
  int widthValue;
  int scrollPosition;
  unsigned long nextFrame;
  Coordinates oldPositionValue;
  bool scrollPositionInitialized;

public:
  void tick(MaskedDisplay* display) override;

  ScrollingText(std::shared_ptr<RenderableText>, int scrollSpeed, int width);
  Coordinates oldPosition() override;
  Coordinates position() override;
  void setPosition(Coordinates coords) override;
  void markRendered() override;
};

#endif
