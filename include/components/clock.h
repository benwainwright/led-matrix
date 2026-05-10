#ifndef CLOCK_H
#define CLOCK_H

#define NOT_SET -1

#include <Arduino.h>
#include "rendering/text.h"
#include "rendering/text-row.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Clock
{

private:
    String withLeadingZeros(int number);
    std::shared_ptr<std::vector<TextRow>> row;

public:
    Clock(MatrixPanel_I2S_DMA *display);

    void setDisplay(MatrixPanel_I2S_DMA *display);
    void tick();
    void init();
    void forceRerender();
    Text &operator[](size_t index);
    std::shared_ptr<std::vector<TextRow>> getText();
};

#endif
