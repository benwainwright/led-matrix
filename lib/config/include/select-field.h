#ifndef SELECT_FIELD_H
#define SELECT_FIELD_H

#include "field.h"
#include "html-node.h"
#include "select-option.h"
#include <Arduino.h>

class SelectField : public Field {
private:
  std::vector<SelectOption> options;
  const std::string nameValue;
  const std::string label;

  const std::string& name() const override;

public:
  SelectField(const std::string& name, const std::string& label, std::vector<SelectOption> options);
  std::unique_ptr<HtmlNode> markup() const override;
};

#endif