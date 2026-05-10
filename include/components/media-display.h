#ifndef MEDIA_DISPLAY_H
#define MEDIA_DISPLAY_H

#include "rendering/text-row.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class MediaDisplay
{
    bool playing;
    std::shared_ptr<std::vector<TextRow>> rows;

public:
    MediaDisplay(
        MatrixPanel_I2S_DMA *display);
    void tick(String title, String artist);
    void setPlaying(bool playing);
    void force();
    std::shared_ptr<std::vector<TextRow>> getText();
};

#endif