#include "renderer.h"
#include "page.h"
#include <Arduino.h>

Renderer::Renderer(std::shared_ptr<MatrixPanel_I2S_DMA> display,
                   std::map<std::string, std::unique_ptr<Renderable>> renderables,
                   std::string initialPage)
    : page(initialPage) {
  for (auto& renderable : renderables) {
    pages.emplace(renderable.first, Page(display, std::move(renderable.second)));
  }
}

void Renderer::render(std::string page) {
  tick();
  showPage(page);
  pages.at(page).render();
}

void Renderer::tick() {
  for (auto& renderable : pages) {
    renderable.second.tick();
  }
}

void Renderer::init() {
  for (auto& renderable : pages) {
    renderable.second.init();
  }
}

void Renderer::showPage(std::string page) {
  if (!(pages.find(page) != pages.end())) {
    return;
  }
  if (page != this->page) {
    pages.at(page).setDirty();
  }
  this->page = page;
}