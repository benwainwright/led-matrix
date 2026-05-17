#ifndef RTT_TOKEN_H
#define RTT_TOKEN_H
#include "error-response.h"
#include "expected.h"
#include "refresh-response.h"
#include <functional>
#include <optional>
#include <string>

class Token {
private:
  std::string refreshToken;
  std::optional<std::string> accessToken;
  std::optional<time_t> expiresAt;
  std::function<tl::expected<RefreshResponse, ErrorResponse>(Token&)> refresh;
  bool hasExpired();

public:
  Token(const std::string& refreshToken,
        std::function<tl::expected<RefreshResponse, ErrorResponse>(Token&)> refreshCallback);

  tl::expected<std::string, ErrorResponse> value();
};

#endif
