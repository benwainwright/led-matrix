#ifndef MEDIA_DISPLAY_H
#define MEDIA_DISPLAY_H

#include "message.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class MediaDisplay
{
    Message message;

public:
    MediaDisplay(
        MatrixPanel_I2S_DMA *display);
    void tick(String title, String artist);
    void force();
};

#endif