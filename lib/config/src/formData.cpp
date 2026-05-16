#include "formData.h"
#include <sstream>

std::string urlDecode(const std::string& value) {
  std::string result;

  for (size_t i = 0; i < value.length(); i++) {
    if (value[i] == '%') {
      if (i + 2 < value.length()) {
        std::string hex = value.substr(i + 1, 2);

        char decoded = static_cast<char>(std::stoi(hex, nullptr, 16));

        result += decoded;
        i += 2;
      }
    } else if (value[i] == '+') {
      result += ' ';
    } else {
      result += value[i];
    }
  }

  return result;
}

std::map<std::string, std::string> parseFormData(const std::string& formData) {
  std::map<std::string, std::string> data;

  std::stringstream stream(formData);
  std::string pair;

  while (std::getline(stream, pair, '&')) {
    size_t equalsPos = pair.find('=');

    if (equalsPos != std::string::npos) {
      std::string key = pair.substr(0, equalsPos);
      std::string value = pair.substr(equalsPos + 1);

      data[urlDecode(key)] = urlDecode(value);
    }
  }

  return data;
}
