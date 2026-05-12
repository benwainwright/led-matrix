#include "media-display.h"
#include "scrolling-text-row.h"

MediaDisplay::MediaDisplay(std::shared_ptr<MatrixPanel_I2S_DMA> display, size_t displayWidth)

    : playing(false),
      rows(std::make_shared<std::vector<std::shared_ptr<RenderableText>>>(
          std::initializer_list<std::shared_ptr<RenderableText>>{

              std::make_shared<ScrollingTextRow>(
                  std::make_shared<TextRow>(
                      display,
                      std::vector<Text>{
                          Text("Artist", Color{150, 150, 150})}),
                  50, displayWidth),

              std::make_shared<ScrollingTextRow>(
                  std::make_shared<TextRow>(
                      display,
                      std::vector<Text>{
                          Text("Title", Color{255, 255, 255})}),
                  50, displayWidth)

          }))
{
}

void MediaDisplay::tick(const String &title, const String &artist)
{
    (*(*rows)[0])[0].setContent(artist);
    (*(*rows)[1])[0].setContent(title);
}

void MediaDisplay::setPlaying(bool isPlaying)
{
    playing = isPlaying;
}

std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> MediaDisplay::getText()
{
    return rows;
}