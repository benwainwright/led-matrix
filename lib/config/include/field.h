#ifndef FIELD_H
#define FIELD_H
#include <Arduino.h>
#include <Pagebuilder.h>
#include <Preferences.h>
#include <memory>
#include <string>

class Field {
  std::string defaultValue;

protected:
  Field(const std::string& defaultValue = "");

private:
  std::string fieldValue;

public:
  virtual std::unique_ptr<HtmlNode> markup() = 0;
  virtual const std::string& name() const = 0;
  void handle(const std::string& value);
  virtual void runHydrate() = 0;
  const std::string& value();
  virtual ~Field() = default;
};
#endif
