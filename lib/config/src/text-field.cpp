#include "text-field.h"
#include <Arduino.h>
#include <Pagebuilder.h>
#include <memory>

TextField::TextField(const std::string& name, const std::string& label, const std::string& type,
                     const std::string& defaultValue, std::function<void(TextField&)> hydrate)
    : HydratableField(std::move(hydrate), std::move(defaultValue)), nameValue(name), label(label),
      type(type) {}

const std::string& TextField::name() const { return nameValue; }

std::unique_ptr<HtmlNode> TextField::getMarkup() {
  return tag("div", children(tag("label", children(text(label.c_str())),
                                 attrs({{"for", nameValue.c_str()}})),
                             tag("input", attrs({{"type", type.c_str()},
                                                 {"value", value()},
                                                 {"name", nameValue.c_str()},
                                                 {"id", nameValue.c_str()}}))));
}
