#ifndef RTT_CLIENT_H
#define RTT_CLIENT_H

#include "error-response.h"
#include "expected.h"
#include "http-method.h"
#include "token.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <map>
#include <optional>
#include <string>

class RequestClient {
private:
  std::string baseUrl;
  WiFiClientSecure wifiClient;
  HTTPClient client;
  Token token;

  std::string buildUrl(const std::string& path, std::map<std::string, std::string> args);

  void getAccessToken();
  tl::expected<JsonDocument, ErrorResponse> request(const std::string& path, HttpMethod method,
                                                    const std::string& token = "",
                                                    std::map<std::string, std::string> args = {});

public:
  RequestClient(const std::string& baseUrl, const std::string& refreshToken);
  tl::expected<JsonDocument, ErrorResponse> get(const std::string& url,
                                                std::map<std::string, std::string> args = {});
};

#endif
