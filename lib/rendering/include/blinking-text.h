#ifndef BLINKING_TEXT_H
#define BLINKING_TEXT_H

#include "renderable-text.h"

class BlinkingText : public RenderableText {
private:
  Color blinkColor;
  int blinkDuration;
  int blinkSpacing;
  int currentDuration;
  unsigned long nextFrame;
  bool blinkOn;

public:
  void tick() override;
  Color color() const override;
  BlinkingText(std::shared_ptr<RenderableText> parent, Color blinkColor, int blinkDuration, int blinkSpacing);
};

#endif