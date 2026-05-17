
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "masked-display.h"

int calculateWidth(const char* string, const GFXfont* font, int fontSize);
int16_t getRenderedWidth(MaskedDisplay& display, std::string content, int x, int y);
int16_t getRenderedHeight(MaskedDisplay& display, std::string content, int x, int y);
int16_t getBoundaryX(MaskedDisplay& display, std::string content, int x, int y);
int16_t getBoundaryY(MaskedDisplay& display, std::string content, int x, int y);

#endif