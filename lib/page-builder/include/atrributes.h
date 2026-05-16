
#ifndef ATTR_H
#define ATTR_H
#include <map>

inline std::map<std::string, std::string>
attrs(std::initializer_list<std::pair<const std::string, std::string>> list) {
  return std::map<std::string, std::string>(list);
}

#endif