#include <Pagebuilder.h>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "pageMarkup.h"
#include "server.h"

ConfigServer::ConfigServer() {}

esp_err_t ConfigServer::handlePost(httpd_req_t* request) {
  std::string response;
  char buffer[100];

  int received;

  while ((received = httpd_req_recv(request, buffer, sizeof(buffer))) > 0) {
    response.append(buffer, received);
  }
  form->handleSubmission(response);
  ESP.restart();
  return ESP_OK;
}

Form& ConfigServer::getForm() const { return *form; }

esp_err_t ConfigServer::handleGet(httpd_req_t* request)

{

  std::ostringstream markup;

  auto html = pageMarkup(form->markup());

  html->render(markup);

  httpd_resp_set_type(request, "text/html");
  httpd_resp_send(request, markup.str().c_str(), HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}

void ConfigServer::start() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  form->hydrate();

  if (httpd_start(&server, &config) == ESP_OK) {

    httpd_uri_t uri_get = {.uri = "/",
                           .method = HTTP_GET,
                           .handler = [](httpd_req_t* request) -> esp_err_t {
                             auto* instance = static_cast<ConfigServer*>(request->user_ctx);
                             return instance->handleGet(request);
                           },
                           .user_ctx = this};
    httpd_register_uri_handler(server, &uri_get);

    httpd_uri_t uri_post = {.uri = "/",
                            .method = HTTP_POST,
                            .handler = [](httpd_req_t* request) -> esp_err_t {
                              auto* instance = static_cast<ConfigServer*>(request->user_ctx);
                              return instance->handlePost(request);
                            },
                            .user_ctx = this};

    httpd_register_uri_handler(server, &uri_post);
  }
}
const std::string& ConfigServer::getValue(const std::string& key) { return form->getValue(key); }

void ConfigServer::setForm(std::unique_ptr<Form> form) { this->form = std::move(form); }