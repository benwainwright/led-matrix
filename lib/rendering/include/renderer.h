#ifndef RENDERER_H
#define RENDERER_H

#include "page.h"
#include <Arduino.h>

class Renderer {
  std::vector<Page> pages;
  uint8_t page;

public:
  Renderer(std::vector<Page> pages);
  void render();
  void showPage(uint8_t number);
};
#endif