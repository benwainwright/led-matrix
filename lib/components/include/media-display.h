#ifndef MEDIA_DISPLAY_H
#define MEDIA_DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

class MediaDisplay {
private:
  bool playing;
  std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> rows;

public:
  MediaDisplay(std::shared_ptr<MatrixPanel_I2S_DMA> display, size_t displayWidth);

  void tick(const String& title, const String& artist);
  void setPlaying(bool playing);

  std::shared_ptr<std::vector<std::shared_ptr<RenderableText>>> getText();
};

#endif