#ifndef REFRESH_RESPONSE_H
#define REFRESH_RESPONSE_H
#include <string>

struct RefreshResponse {
  std::string accessToken;
  time_t validUntil;
};
#endif