#ifndef CLOCK_H
#define CLOCK_H

#define NOT_SET -1

#include <Arduino.h>
#include "message.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Clock
{

private:
    Message message;
    String withLeadingZeros(int number);

public:
    Clock(MatrixPanel_I2S_DMA *display);
    void setDisplay(MatrixPanel_I2S_DMA *display);
    void tick();
    void init();
    void forceRerender();
};

#endif
