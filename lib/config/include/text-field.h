#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H
#include "field.h"
#include "html-node.h"
#include "hydratable-field.h"
#include <Arduino.h>

class TextField : public HydratableField<TextField> {
protected:
  std::unique_ptr<HtmlNode> getMarkup() override;

private:
  std::string nameValue;
  std::string label;
  std::string type;
  const std::string& name() const override;

public:
  TextField(const std::string& name, const std::string& label, const std::string& type = "text",
            const std::string& defaultVallue = "",
            std::function<void(TextField&)> hydrate = nullptr);
};

#endif