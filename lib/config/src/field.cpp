#include "field.h"

std::string Field::value() const
{
    Preferences preferences;
    if (!preferences.begin("config", true))
    {
        Serial.println("Failed to open preferences for reading");
        return "";
    }

    String storedValue = preferences.getString(name().c_str(), "");
    preferences.end();
    return std::string(storedValue.c_str());
}

void Field::handle(const std::string &value)
{
    Preferences preferences;
    if (!preferences.begin("config", false))
    {
        Serial.println("Failed to open preferences for writing");
        return;
    }

    preferences.putString(name().c_str(), value.c_str());
    preferences.end();
}
