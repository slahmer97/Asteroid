//
// Created by stevlulz on 11/04/2020.
//

#ifndef ASTEROID_REST_SERVER_H
#define ASTEROID_REST_SERVER_H

#include <iostream>
#include "server_http_service_handler.h"
#include "server_ws.hpp"
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

class rest_server {
    rest_server();

public:
    void init(std::string& host, std::string& port);

    void run();
    void on_message(const std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::InMessage> in_message);
    void on_open(const std::shared_ptr<WsServer::Connection>& connection);
    void on_close(const std::shared_ptr<WsServer::Connection>& connection, int status, const std::string & );
    void on_handshake(std::shared_ptr<WsServer::Connection> /*connection*/, SimpleWeb::CaseInsensitiveMultimap &);
    static std::shared_ptr<rest_server> get_instance();
private:
    WsServer* m_g_httpHandler;
    std::string m_uri;

    static std::shared_ptr<rest_server> m_rest_server;
};


#endif //ASTEROID_REST_SERVER_H
