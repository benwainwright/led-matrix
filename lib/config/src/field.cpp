#include "field.h"

Field::Field(const std::string& defaultValue) : defaultValue(defaultValue) {}

const std::string& Field::value() {
  Preferences preferences;
  if (!preferences.begin("config", true)) {
    Serial.println("Failed to open preferences for reading");
    return defaultValue;
  }

  fieldValue = preferences.getString(name().c_str(), "").c_str();
  preferences.end();
  if (fieldValue == "") {
    return defaultValue;
  }
  return fieldValue;
}

void Field::handle(const std::string& value) {
  Preferences preferences;
  if (!preferences.begin("config", false)) {
    Serial.println("Failed to open preferences for writing");
    return;
  }

  preferences.putString(name().c_str(), value.c_str());
  preferences.end();
}
