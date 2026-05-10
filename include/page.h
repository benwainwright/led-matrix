#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "text.h"
#include "text-row.h"

class Page
{
private:
    bool pageDirty;
    std::shared_ptr<std::vector<TextRow>> rows;
    MatrixPanel_I2S_DMA *display;
    void renderRow(TextRow &row, uint8_t index);
    int16_t getHeightOffsetForCentre(const char *message, uint8_t index, uint8_t count);
    int16_t getWidthOffsetForCentre(const char *message);
    int16_t getWidthOfTextItem(const Text &text, int16_t x, int16_t y);
    bool isDirty();

public:
    Page(
        MatrixPanel_I2S_DMA *display,
        std::shared_ptr<std::vector<TextRow>> rows);
    void setRow(uint8_t rowNumber, std::vector<Text> row);
    void render();
    void setDirty();
};
#endif
