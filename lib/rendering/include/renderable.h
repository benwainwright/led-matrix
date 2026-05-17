#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "renderable-text-row.h"

#include <memory>
#include <vector>

class Renderable {
public:
  virtual std::vector<std::shared_ptr<RenderableTextRow>> getText() = 0;
  virtual void tick() {};
  virtual void init() {};
  virtual int gap() { return 1; }
  virtual bool verticallyAlign() { return true; };
};

#endif