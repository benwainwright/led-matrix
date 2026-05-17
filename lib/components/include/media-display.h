#ifndef MEDIA_DISPLAY_H
#define MEDIA_DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

#include "renderable.h"

class MediaDisplay : public Renderable {
private:
  bool playing;
  std::vector<std::shared_ptr<RenderableTextRow>> rows;
  std::function<void(MediaDisplay&)> onTick;

public:
  MediaDisplay(size_t displayWidth, std::function<void(MediaDisplay&)> onTick = nullptr);
  void setMedia(const String& title, const String& artist);
  void setPlaying(bool playing);
  void tick() override;
  bool verticallyAlign() { return false; }

  std::vector<std::shared_ptr<RenderableTextRow>> getText() override;
};

#endif