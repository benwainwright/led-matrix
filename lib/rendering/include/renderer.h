#ifndef RENDERER_H
#define RENDERER_H

#include "page.h"
#include "renderable.h"
#include <Arduino.h>
#include <map>

class Renderer {
private:
  std::map<std::string, Page> pages;
  std::string page;
  void showPage(std::string page);
  void tick();

public:
  Renderer(std::shared_ptr<MatrixPanel_I2S_DMA> display,
           std::map<std::string, std::unique_ptr<Renderable>> pages, std::string initialPage);
  void render(std::string page);
  void init();
};
#endif