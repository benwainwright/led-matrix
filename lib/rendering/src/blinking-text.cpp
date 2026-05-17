#include "blinking-text.h"
BlinkingText::BlinkingText(std::shared_ptr<RenderableText> parent, Color blinkColor, int blinkDuration,
                           int blinkSpacing)
    : RenderableText(parent), blinkColor(blinkColor), blinkDuration(blinkDuration), blinkSpacing(blinkSpacing),
      nextFrame(millis()), blinkOn(false) {}

void BlinkingText::tick() {
  auto now = millis();

  auto interval = blinkOn ? blinkDuration : blinkSpacing;

  if ((now - nextFrame) >= interval) {

    nextFrame += interval;
    blinkOn = !blinkOn;
    setDirty();
  }
}

Color BlinkingText::color() const {
  if (blinkOn) {
    return blinkColor;
  }
  return parent->color();
}
