#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include "esp_http_server.h"
#include "form.h"

class ConfigServer
{
public:
    ConfigServer(std::unique_ptr<Form> form);
    void start();

private:
    httpd_handle_t server;
    std::shared_ptr<Form> form;

    esp_err_t handleGet(httpd_req_t *request);
    esp_err_t handlePost(httpd_req_t *request);
};
#endif