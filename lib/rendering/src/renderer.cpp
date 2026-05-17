#include "renderer.h"
#include "page.h"
#include <Arduino.h>

Renderer::Renderer(std::shared_ptr<MatrixPanel_I2S_DMA> display,
                   std::map<std::string, std::unique_ptr<Renderable>> renderables, std::string initialPage,
                   const GFXfont* defaultFont)
    : page(initialPage), defaultFont(defaultFont) {
  for (auto& renderable : renderables) {
    auto gap = renderable.second->gap();
    auto verticallyAlign = renderable.second->verticallyAlign();
    pages.emplace(renderable.first, Page(display, std::move(renderable.second), defaultFont, gap, verticallyAlign));
  }
}

void Renderer::render(std::string page) {
  this->tick();
  this->showPage(page);
  this->pages.at(page).render();
}

void Renderer::tick() {
  for (auto& renderable : this->pages) {
    renderable.second.tick();
  }
}

void Renderer::init() {
  for (auto& renderable : this->pages) {
    renderable.second.init();
  }
}

void Renderer::showPage(std::string page) {
  if (!(this->pages.find(page) != this->pages.end())) {
    return;
  }
  if (page != this->page) {
    this->pages.at(page).clear();
    this->pages.at(page).setDirty();
    this->page = page;
  }
}
