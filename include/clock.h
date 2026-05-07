#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

class Clock
{

private:
    String previousTime;
    String withLeadingZeros(int number);

public:
    void tick();
    void init();
};

#endif
