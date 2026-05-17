#include "request-client.h"
#include "error-response.h"
#include "expected.h"
#include "http-method.h"
#include "parse-iso-date.h"
#include <HTTPClient.h>
#include <UrlEncode.h>

#include <sstream>
#include <stdexcept>

RequestClient::RequestClient(const std::string& baseUrl, const std::string& refreshToken)
    : baseUrl(std::move(baseUrl)),
      token(
          Token(refreshToken,
                [this, refreshToken](Token& token) -> tl::expected<RefreshResponse, ErrorResponse> {
                  auto response = this->request("api/get_access_token", GET, refreshToken);
                  if (response.has_value()) {
                    std::string responseToken = response.value()["token"];
                    std::string validUntil = response.value()["validUntil"];
                    return RefreshResponse{responseToken, parseIso8601(validUntil)};
                  } else {
                    return tl::unexpected(response.error());
                  }
                })) {
  wifiClient.setInsecure();
}

tl::expected<JsonDocument, ErrorResponse>
RequestClient::get(const std::string& path, std::map<std::string, std::string> args) {
  auto accessToken = token.value();
  if (!accessToken.has_value()) {
    return tl::unexpected(accessToken.error());
  }

  return request(path, GET, accessToken.value(), args);
}

std::string RequestClient::buildUrl(const std::string& path,
                                    std::map<std::string, std::string> args) {
  std::stringstream ss;

  auto baseUrlEndsWithSlash = !baseUrl.empty() && baseUrl.back() == '/';
  auto pathStartsWithSlash = !path.empty() && path.front() == '/';

  if (baseUrlEndsWithSlash && pathStartsWithSlash) {
    ss << baseUrl << path.substr(1);
  } else if (!baseUrlEndsWithSlash && !pathStartsWithSlash) {
    ss << baseUrl << "/" << path;
  } else {
    ss << baseUrl << path;
  }

  if (args.empty()) {
    return ss.str();
  }

  ss << "?";

  int count = 0;

  for (auto& pair : args) {
    auto encoded = urlEncode(pair.second.c_str());
    ss << pair.first << "=" << encoded.c_str();
    if (count < args.size() - 1) {
      ss << "&";
    }
    count++;
  }

  return ss.str();
}

tl::expected<JsonDocument, ErrorResponse>
RequestClient::request(const std::string& path, HttpMethod method, const std::string& token,
                       std::map<std::string, std::string> args) {

  std::string url = buildUrl(path, args);
  client.begin(wifiClient, url.c_str());

  if (token != "") {
    client.addHeader("Authorization", std::string("Bearer " + token).c_str());
  }

  int responseCode;

  switch (method) {
  case GET:
    Serial.printf("Making GET request to url: %s\n", url.c_str());
    responseCode = client.GET();
    break;
  default:
    throw std::runtime_error("Only GET requests currently supported");
  };

  Serial.printf("Responded with status code %d\n", responseCode);

  if (responseCode < 0) {
    client.end();
    return tl::unexpected(ErrorResponse{responseCode, ""});
  }

  auto response = client.getString();
  if (responseCode > 0 && responseCode < 399) {
    JsonDocument document;
    deserializeJson(document, response);
    client.end();
    return document;
  }
  client.end();
  return tl::unexpected(ErrorResponse{responseCode, std::string(response.c_str())});
}
