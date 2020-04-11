//
// Created by stevlulz on 11/04/2020.
//

#ifndef ASTEROID_REST_SERVER_H
#define ASTEROID_REST_SERVER_H

#include <iostream>
#include "server_http_service_handler.h"

class rest_server {
    inline rest_server() noexcept = default;
    void on_shutdown();
    void on_initialize();
public:
    void init(std::string& host, std::string& port);

    void run();

    static std::shared_ptr<rest_server> get_instance();
private:
    std::unique_ptr<server_http_service_handler> m_g_httpHandler;
    std::string m_uri;

    static std::shared_ptr<rest_server> m_rest_server;
};


#endif //ASTEROID_REST_SERVER_H
