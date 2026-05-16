#ifndef FORMDATA_H
#define FORMDATA_H

#include <map>
#include <string>
std::string urlDecode(const std::string& value);
std::map<std::string, std::string> parseFormData(const std::string& formData);
#endif