#include "token.h"
#include <Arduino.h>
#include <stdexcept>
#include <time.h>

Token::Token(const std::string& refreshToken,
             std::function<tl::expected<RefreshResponse, ErrorResponse>(Token&)> refreshCallback)
    : refreshToken(refreshToken), refresh(refreshCallback) {}

bool Token::hasExpired() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    throw std::runtime_error("Failed to obtain time");
  }

  auto time = mktime(&timeinfo);

  return expiresAt < time;
}

const std::string& Token::value() {
  if (!accessToken.has_value() || hasExpired()) {
    auto newToken = refresh(*this);
    if (newToken.has_value()) {
      accessToken = newToken->accessToken;
      expiresAt = newToken->validUntil;
    }
  }

  return accessToken.value();
}