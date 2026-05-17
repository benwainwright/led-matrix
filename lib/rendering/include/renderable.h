#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "renderable-text.h"

#include <memory>
#include <vector>

class Renderable {
public:
  virtual std::vector<std::shared_ptr<RenderableText>> getText() = 0;
  virtual void tick() {};
  virtual void init() {};
  virtual int gap() { return 1; }
  virtual bool verticallyAlign() { return true; };
};

#endif