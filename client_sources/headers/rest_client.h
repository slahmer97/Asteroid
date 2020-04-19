//
// Created by stevlulz on 08/04/2020.
//

#ifndef ASTEROID_REST_CLIENT_H
#define ASTEROID_REST_CLIENT_H


#include <memory>
#include <client_ws.hpp>
#include "client_http_service_handler.h"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

class rest_client {
private:
    inline rest_client() {
        m_server_uri = "empty";
    }
    void client_gui();
    void client_network();

    void send_create_game_message();
    void send_join_game_message(const std::string& game_id);
    void on_message(std::shared_ptr<WsClient::Connection> connection, std::shared_ptr<WsClient::InMessage> in_message);
    void on_open(std::shared_ptr<WsClient::Connection> connection);
    void on_close(std::shared_ptr<WsClient::Connection> connection, int status, const std::string & reason);
    void on_error(std::shared_ptr<WsClient::Connection> connection, const SimpleWeb::error_code &ec);
    std::string send_message(const std::string& message);
public:
    void init(std::string& host, std::string& port);
    void run();
   static std::shared_ptr<rest_client> get_instance() noexcept;


private:
    WsClient*   m_g_httpHandler;
    std::string m_uri;
    std::string m_server_uri;
    static std::shared_ptr<rest_client> s_rest_client;

};


#endif //ASTEROID_REST_CLIENT_H
