
#ifndef RENDERABLE_TEXT_H
#define RENDERABLE_TEXT_H

#include "alignment.h"
#include "color.h"
#include "coordinates.h"
#include "masked-display.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <memory>
#include <optional>

class RenderableText {

protected:
  RenderableText() = default;
  RenderableText(std::shared_ptr<RenderableText> parent) : parent(parent) {}
  std::shared_ptr<RenderableText> parent;

private:
public:
  virtual void setContent(const String& content) { this->parent->setContent(content); };
  virtual const String& content() const { return this->parent->content(); };
  virtual void setColor(Color color) { this->parent->setColor(color); };
  virtual Color color() const { return this->parent->color(); };
  virtual void setDefaultFont(const GFXfont* font) { this->parent->setDefaultFont(font); };
  virtual void setDirty() { this->parent->setDirty(); };
  virtual void tick(MaskedDisplay* display) {};
  virtual Coordinates oldPosition() { return this->parent->oldPosition(); }
  virtual Coordinates position() { return this->parent->position(); };
  virtual void setPosition(Coordinates coords) { this->parent->setPosition(coords); };
  virtual int getFontSize() { return this->parent->getFontSize(); }
  virtual const GFXfont* font() { return this->parent->font(); };
  virtual bool isDirty() const { return this->parent->isDirty(); };
  virtual void markRendered() { this->parent->markRendered(); };
};

#endif
