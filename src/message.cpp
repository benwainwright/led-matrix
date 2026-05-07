#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Arduino.h>
#include "message.h"
#include "constants.h"

Message::Message(
    MatrixPanel_I2S_DMA *display,
    uint8_t sizeInit, int8_t xInit, int8_t yInit)
    : display(display), size(sizeInit), x(xInit), y(yInit), forceRerender(false)
{
}

void Message::setDisplay(MatrixPanel_I2S_DMA *nextDisplay)
{
  display = nextDisplay;
}

void Message::render(const char *theMessage, int8_t x, int8_t y)
{

  if (String(theMessage) == message && !forceRerender)
  {
    return;
  }

  message = String(theMessage);

  if (display == nullptr)
  {
    return;
  }

  forceRerender = false;

  display->clearScreen();
  display->setTextColor(display->color565(255, 255, 255));
  display->setCursor(x, y);
  display->print(theMessage);
}

int16_t Message::getWidthOffsetForCentre(const char *message)
{
  if (display == nullptr)
  {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  return ((display->width() - w) / 2) - x1;
}

int16_t Message::getHeightOffsetForCentre(const char *message)
{
  if (display == nullptr)
  {
    return 0;
  }

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  return ((display->height() - h) / 2) - y1;
}

void Message::write(String message)
{
  write(message.c_str());
}

void Message::write(const char *message)
{
  if (display == nullptr)
  {
    return;
  }

  display->setTextSize(size);

  int8_t trueX = x == X_CENTRED ? getWidthOffsetForCentre(message) : x;
  int8_t trueY = y == Y_CENTRED ? getHeightOffsetForCentre(message) : y;

  render(message, trueX, trueY);
}

void Message::write(std::vector<String> lines)
{

  String withNewlines;

  for (size_t i = 0; i < lines.size(); i++)
  {
    if (i != 0)
    {
      withNewlines += "\r\n";
    }
    withNewlines += lines[i];
  }

  write(withNewlines);
}

void Message::force()
{
  forceRerender = true;
}
