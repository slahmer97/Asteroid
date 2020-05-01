//
// Created by stevlulz on 08/04/2020.
//

#ifndef ASTEROID_REST_CLIENT_H
#define ASTEROID_REST_CLIENT_H


#include <memory>
#include <thread>
#include <client_ws.hpp>
#include "client_http_service_handler.h"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

class rest_client {
private:
    inline rest_client() {
        m_server_uri = "empty";
    }

    [[noreturn]] void client_gui();
    void client_network();

    void send_create_game_message();
    void send_join_game_message();
    void send_move_forward_message();
    void send_move_backward_message();
    void send_rotate_left_message();
    void send_rotate_right_message();
    void send_fire_message();

    void set_username(std::string&& username);
    void set_game_id(std::string&& game_id);
    void fast_config(std::string&& salon, std::string&& joueur, std::unique_ptr<std::thread>& gui,
                     std::unique_ptr<std::thread>& net, bool creer_salon);

    void on_message(const std::shared_ptr<WsClient::Connection>& connection,const std::shared_ptr<WsClient::InMessage>& in_message);
    void on_open(std::shared_ptr<WsClient::Connection>& connection);
    void on_close(const std::shared_ptr<WsClient::Connection>& connection, int status, const std::string & reason);
    void on_error(const std::shared_ptr<WsClient::Connection>& connection, const SimpleWeb::error_code &ec);
    std::string send_message(const std::string& message);

public:
    void init(std::string& host, std::string& port);
    void run();
   static std::shared_ptr<rest_client> get_instance() noexcept;


private:
    WsClient*   m_g_httpHandler;
    std::shared_ptr<WsClient::Connection> m_connection;
    std::string m_uri;
    std::string m_server_uri;
    static std::shared_ptr<rest_client> s_rest_client;
    std::string m_username;
    std::string m_game_id;

};


#endif //ASTEROID_REST_CLIENT_H
