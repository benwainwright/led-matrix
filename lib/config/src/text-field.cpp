#include "text-field.h"
#include <Arduino.h>
#include <Pagebuilder.h>
#include <memory>

TextField::TextField(const std::string& name, const std::string& label)
    : nameValue(name), label(label) {}

const std::string& TextField::name() const { return nameValue; }

std::unique_ptr<HtmlNode> TextField::markup() const {
  return tag("div", children(tag("label", children(text(label.c_str())),
                                 attrs({{"for", nameValue.c_str()}})),
                             tag("input", attrs({{"type", "text"},
                                                 {"value", value()},
                                                 {"name", nameValue.c_str()},
                                                 {"id", nameValue.c_str()}}))));
}
