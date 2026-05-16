#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H
#include "field.h"
#include "html-node.h"
#include <Arduino.h>

class TextField : public Field {
private:
  std::string nameValue;
  std::string label;
  const std::string& name() const override;

public:
  TextField(const std::string& name, const std::string& label);
  std::unique_ptr<HtmlNode> markup() const override;
};

#endif