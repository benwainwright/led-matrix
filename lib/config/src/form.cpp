#include "form.h"
#include "formData.h"

#include <sstream>
#include <stdexcept>

void Form::render(std::ostream& out) {}

void Form::hydrate() {
  for (auto& field : fields) {
    field->runHydrate();
  }
}

void Form::handleSubmission(const std::string& formData) {
  auto data = parseFormData(formData);

  for (auto& field : fields) {
    if (data.find(field->name()) != data.end()) {
      auto theNewValue = data[field->name()];
      field->handle(theNewValue);
    }
  }
}

const std::string& Form::getValue(const std::string& key) {
  for (auto& field : fields) {
    if (field->name() == key) {
      return field->value();
    }
  }
  throw std::invalid_argument("key not found");
}

std::unique_ptr<HtmlNode> Form::markup() const {
  std::vector<std::unique_ptr<HtmlNode>> fieldNodes;

  for (const auto& field : fields) {
    fieldNodes.push_back(field->markup());
  }

  fieldNodes.push_back(
      tag("div", attrs({{"class", "submitRow"}}),
          children(tag("button", children(text("Save")), attrs({{"type", "submit"}})))));
  return tag("form", std::move(fieldNodes), attrs({{"method", "POST"}}));
}

void Form::setFields(std::vector<std::unique_ptr<Field>> fields) {
  this->fields = std::move(fields);
}
