#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "message.h"
#include "constants.h"

Message::Message(
    MatrixPanel_I2S_DMA *display, uint8_t sizeInit, int8_t xInit, int8_t yInit)
    : display(display), size(sizeInit), x(xInit), y(yInit)
{
}

void Message::render(const char *message, int8_t x, int8_t y)
{

  if (display == nullptr)
  {
    return;
  }

  display->clearScreen();
  display->setTextSize(size);
  display->setTextColor(display->color565(255, 255, 255));
  display->setCursor(x, y);
  display->print(message);
}

uint16_t Message::getWidthOffsetForCentre(const char *message)
{

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  return (display->width() - w) / 2;
}

uint16_t Message::getHeightOffsetForCentre(const char *message)
{

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  return (display->height() - h) / 2;
}

void Message::write(String message)
{
  write(message.c_str());
}

void Message::write(const char *message)
{
  int8_t trueX = x == X_CENTRED ? getWidthOffsetForCentre(message) : x;
  int8_t trueY = y == Y_CENTRED ? getHeightOffsetForCentre(message) : y;

  render(message, trueX, trueY);
}
