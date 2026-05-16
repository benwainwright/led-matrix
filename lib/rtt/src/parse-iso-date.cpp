#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

time_t parseIso8601(const std::string& iso) {
  std::tm tm = {};

  std::istringstream ss(iso.substr(0, 19));
  ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

  setenv("TZ", "UTC0", 1);
  tzset();

  return mktime(&tm);
}