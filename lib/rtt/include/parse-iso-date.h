#ifndef PARSE_ISO_DATE_H
#define PARSE_ISO_DATE_H
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

time_t parseIso8601(const std::string& iso);

#endif