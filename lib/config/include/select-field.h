#ifndef SELECT_FIELD_H
#define SELECT_FIELD_H

#include "field.h"
#include "html-node.h"
#include "hydratable-field.h"
#include "select-option.h"
#include <Arduino.h>

class SelectField : public HydratableField<SelectField> {
protected:
  std::unique_ptr<HtmlNode> getMarkup() override;

private:
  std::vector<SelectOption> options;
  const std::string nameValue;
  const std::string label;

  const std::string& name() const override;

public:
  SelectField(const std::string& name, const std::string& label, std::vector<SelectOption> options,
              const std::string& defaultValue = "",
              std::function<void(SelectField&)> hydrate = nullptr);
  void setOptions(std::vector<SelectOption> options);
};

#endif