#include <Pagebuilder.h>
#include <sstream>
#include <ostream>
#include <string>
#include <memory>

#include "server.h"
#include "pageMarkup.h"

ConfigServer::ConfigServer(std::unique_ptr<Form> form) : server(nullptr), form(std::move(form)) {}

esp_err_t ConfigServer::handlePost(httpd_req_t *request)
{
    std::string response;
    char buffer[100];

    int received;

    while ((received = httpd_req_recv(request, buffer, sizeof(buffer))) > 0)
    {
        response.append(buffer, received);
    }
    form->handleSubmission(response);
    return ESP_OK;
}

esp_err_t ConfigServer::handleGet(httpd_req_t *request)

{
    std::ostringstream markup;

    auto html = pageMarkup(form->markup());

    html->render(markup);

    httpd_resp_set_type(request, "text/html");
    httpd_resp_send(request, markup.str().c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

void ConfigServer::start()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK)
    {

        httpd_uri_t uri_get = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = [](httpd_req_t *request) -> esp_err_t
            {
                auto *instance = static_cast<ConfigServer *>(request->user_ctx);
                return instance->handleGet(request);
            },
            .user_ctx = this};
        httpd_register_uri_handler(server, &uri_get);

        httpd_uri_t uri_post = {
            .uri = "/",
            .method = HTTP_POST,
            .handler = [](httpd_req_t *request) -> esp_err_t
            {
                auto *instance = static_cast<ConfigServer *>(request->user_ctx);
                return instance->handlePost(request);
            },
            .user_ctx = this};

        httpd_register_uri_handler(server, &uri_post);
    }
}