#include "media-display.h"

#include "message.h"

MediaDisplay::MediaDisplay(
    MatrixPanel_I2S_DMA *display) : rows(std::make_shared<std::vector<TextRow>>(std::initializer_list<TextRow>{
                                        TextRow(
                                            {Text("Artist", Color{150, 150, 150})}),
                                        TextRow(
                                            {Text("Title", Color{255, 255, 255})}),
                                    }))

{
}

void MediaDisplay::tick(String title, String artist)
{
    (*rows)[0][0].setContent(artist);
    (*rows)[1][0].setContent(title);
}

void MediaDisplay::setPlaying(bool isPlaying)
{
    playing = isPlaying;
}

std::shared_ptr<std::vector<TextRow>> MediaDisplay::getText()
{
    return rows;
}

void MediaDisplay::force()
{
}