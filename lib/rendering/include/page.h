#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "text-row.h"
#include "renderable-text.h"

class Page
{
private:
    bool pageDirty;
    size_t gap;
    std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> rows;
    MatrixPanel_I2S_DMA *display;
    void renderRow(RenderableText &row, uint8_t index);
    void positionRow(RenderableText &row, uint8_t index);
    int16_t getHeightOffsetForCentre(const char *message, uint8_t index, uint8_t count);
    int16_t getWidthOffsetForCentre(const char *message);
    int16_t getWidthOfTextItem(const Text &text, int16_t x, int16_t y);
    bool isDirty();

public:
    Page(
        MatrixPanel_I2S_DMA *display,
        std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> rows);
    Page(
        MatrixPanel_I2S_DMA *display,
        std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> rows, size_t gap);
    void setRow(uint8_t rowNumber, std::vector<Text> row);
    void render();
    void setDirty();
};
#endif
