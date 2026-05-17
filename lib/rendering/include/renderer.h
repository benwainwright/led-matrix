#ifndef RENDERER_H
#define RENDERER_H

#include "page.h"
#include "renderable.h"
#include "masked-display.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <map>
#include <optional>

class Renderer {
private:
  std::map<std::string, Page> pages;
  std::string page;
  const GFXfont* defaultFont;
  void showPage(std::string page);
  void tick();

public:
  Renderer(std::shared_ptr<MaskedDisplay> display, std::map<std::string, std::unique_ptr<Renderable>> pages,
           std::string initialPage, const GFXfont* defaultFont);
  void render(std::string page);
  void init();
};
#endif