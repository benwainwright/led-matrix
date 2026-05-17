#include "media-display.h"
#include "scrolling-text-row.h"

MediaDisplay::MediaDisplay(size_t displayWidth, std::function<void(MediaDisplay&)> onTick)
    : playing(false),
      rows(std::initializer_list<std::shared_ptr<RenderableTextRow>>{

          std::make_shared<ScrollingTextRow>(
              std::make_shared<TextRow>(
                  std::vector<std::shared_ptr<RenderableText>>{std::make_shared<Text>("Artist", Color{150, 150, 150})},
                  CENTRE),
              50, displayWidth),

          std::make_shared<ScrollingTextRow>(
              std::make_shared<TextRow>(
                  std::vector<std::shared_ptr<RenderableText>>{std::make_shared<Text>("Title", Color{255, 255, 255})},
                  CENTRE),
              50, displayWidth)

      }),
      onTick(onTick) {}

void MediaDisplay::setMedia(const String& title, const String& artist) {
  (*(rows)[0])[0].setContent(artist);
  (*(rows)[1])[0].setContent(title);
}

void MediaDisplay::tick() {
  if (onTick != nullptr) {
    onTick(*this);
  }
}

void MediaDisplay::setPlaying(bool isPlaying) { playing = isPlaying; }

std::vector<std::shared_ptr<RenderableTextRow>> MediaDisplay::getText() { return rows; }