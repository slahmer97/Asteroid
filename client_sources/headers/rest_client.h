//
// Created by stevlulz on 08/04/2020.
//

#ifndef ASTEROID_REST_CLIENT_H
#define ASTEROID_REST_CLIENT_H


#include <bits/unique_ptr.h>
#include "client_http_service_handler.h"

class rest_client {
    inline rest_client() noexcept = default;
    void on_shutdown();
    void on_initialize();
    void client_gui();
    void client_network();
public:
    void init(std::string& host, std::string& port);

    void run();

   static std::shared_ptr<rest_client> get_instance() noexcept;
private:
    std::unique_ptr<client_http_service_handler> m_g_httpHandler;
    std::string m_uri;

    static std::shared_ptr<rest_client> s_rest_client;

};


#endif //ASTEROID_REST_CLIENT_H
