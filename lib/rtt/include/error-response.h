#ifndef ERROR_RESPONSE_H
#define ERROR_RESPONSE_H
#include <ArduinoJson.h>
struct ErrorResponse {
  int statusCode;
  std::string responseBody;
};
#endif