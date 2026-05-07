#include "media-display.h"

#include "message.h"

MediaDisplay::MediaDisplay(
    MatrixPanel_I2S_DMA *display) : message(Message(display, 1, X_CENTRED, Y_CENTRED))
{
}

void MediaDisplay::tick(String title, String artist)
{
    if (playing)
    {
        message.write({title, artist});
    }
    else
    {
        message.write("Idle");
    }
}

void MediaDisplay::setPlaying(bool isPlaying)
{
    playing = isPlaying;
}

void MediaDisplay::force()
{
    message.force();
}