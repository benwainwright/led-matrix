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
  Form(std::vector<std::unique_ptr<Field>> fields);
  void render(std::ostream& out);
  void handleSubmission(const std::string& formData);
};
#endif