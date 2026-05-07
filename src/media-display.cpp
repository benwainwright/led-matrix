#include "media-display.h"

MediaDisplay::MediaDisplay(
    MatrixPanel_I2S_DMA *display) : message(Message(display, 1, 1, 1))
{
}

void MediaDisplay::tick(String title, String artist)
{
    message.write({title, artist});
}

void MediaDisplay::force()
{
    message.force();
}