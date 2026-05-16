#ifndef FORM_H
#define FORM_H
#include "field.h"
#include <Arduino.h>
#include <Pagebuilder.h>
#include <memory>

class Form {
private:
  std::vector<std::unique_ptr<Field>> fields;

public:
  std::unique_ptr<HtmlNode> markup() const;
  Form() = default;
  void render(std::ostream& out);
  void hydrate();
  void handleSubmission(const std::string& formData);
  const std::string& getValue(const std::string& key);

  void setFields(std::vector<std::unique_ptr<Field>> fields);
};
#endif