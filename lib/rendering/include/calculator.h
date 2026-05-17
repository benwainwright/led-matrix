
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

int calculateWidth(const char* string, const GFXfont* font, int fontSize);
int16_t getRenderedWidth(MatrixPanel_I2S_DMA& display, std::string content, int x, int y);
int16_t getRenderedHeight(MatrixPanel_I2S_DMA& display, std::string content, int x, int y);
int16_t getBoundaryX(MatrixPanel_I2S_DMA& display, std::string content, int x, int y);
int16_t getBoundaryY(MatrixPanel_I2S_DMA& display, std::string content, int x, int y);

#endif