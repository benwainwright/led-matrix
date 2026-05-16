#include <Pagebuilder.h>

#include "select-field.h"

SelectField::SelectField(const std::string& name, const std::string& label,
                         std::vector<SelectOption> options, const std::string& defaultValue,
                         std::function<void(SelectField&)> hydrate)
    : HydratableField(std::move(hydrate), std::move(defaultValue)), options(std::move(options)),
      nameValue(name), label(label) {}

const std::string& SelectField::name() const { return nameValue; }

std::unique_ptr<HtmlNode> SelectField::getMarkup() {

  std::vector<std::unique_ptr<HtmlNode>> optionNodes;

  for (const auto& option : options) {
    auto attributes = option.value == this->value()
                          ? attrs({{"value", option.value}, {"selected", "true"}})
                          : attrs({{"value", option.value}});
    optionNodes.push_back(tag("option", attributes, children(text(option.label))));
  }

  return tag(
      "div",
      children(tag("label", children(text(label.c_str())), attrs({{"for", nameValue.c_str()}})),
               tag("select", attrs({{"name", nameValue.c_str()}, {"id", nameValue.c_str()}}),
                   std::move(optionNodes))));
}

void SelectField::setOptions(std::vector<SelectOption> options) { this->options = options; }
