#include "renderer.h"
#include "page.h"
#include <Arduino.h>

Renderer::Renderer(std::vector<Page> pages) : pages(pages), page(0) {}

void Renderer::render() { pages[page].render(); }

void Renderer::showPage(uint8_t pageNumber) {
  if (pageNumber >= pages.size()) {
    return;
  }
  if (page != pageNumber) {
    pages[pageNumber].setDirty();
  }
  page = pageNumber;
}