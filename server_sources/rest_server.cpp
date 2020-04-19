//
// Created by stevlulz on 11/04/2020.
//

#include "rest_server.h"

#include <utility>
#include <future>

std::shared_ptr<rest_server> rest_server::m_rest_server;




void rest_server::init(std::string &host, std::string &port) {
    m_g_httpHandler->config.port = std::stoi(port);

    m_g_httpHandler->endpoint["^/echo/?$"].on_message = [&](const std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::InMessage> in_message) {
        this->on_message(connection,std::move(in_message));
    };
    m_g_httpHandler->endpoint["^/echo/?$"].on_open = [&](const std::shared_ptr<WsServer::Connection>& connection) {
       this->on_open(connection);
    };

    m_g_httpHandler->endpoint["^/echo/?$"].on_close = [&](const std::shared_ptr<WsServer::Connection>& connection, int status, const std::string &  reason/*reason*/) {

        this->on_close(connection,status,reason);
    };

    // Can modify handshake response headers here if needed
    m_g_httpHandler->endpoint["^/echo/?$"].on_handshake = [](const std::shared_ptr<WsServer::Connection>& /*connection*/, SimpleWeb::CaseInsensitiveMultimap & /*response_header*/) {
        return SimpleWeb::StatusCode::information_switching_protocols; // Upgrade to websocket
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    m_g_httpHandler->endpoint["^/echo/?$"].on_error = [](const std::shared_ptr<WsServer::Connection>& connection, const SimpleWeb::error_code &ec) {

    };

}

void rest_server::run(){

    std::promise<unsigned short> server_port;
    std::thread server_thread([&]() {
        // Start server
        this->m_g_httpHandler->start([&server_port](unsigned short port) {
            server_port.set_value(port);
        });
    });
    std::string a;
    std::cout<<"Enter something to exit\n";
    std::cin>>a;

}

std::shared_ptr<rest_server> rest_server::get_instance()  {
    if(rest_server::m_rest_server == nullptr)
        rest_server::m_rest_server = std::make_shared<rest_server>(rest_server());
    return rest_server::m_rest_server;
}
void rest_server::on_open(const std::shared_ptr<WsServer::Connection>& connection) {
    std::cout<<"On open\n";
}

void rest_server::on_message(const std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::InMessage> in_message) {
    std::cout<<"On message\n";
}

void rest_server::on_close(const std::shared_ptr<WsServer::Connection>& connection, int status, const std::string &) {
    std::cout<<"On close\n";
}
void rest_server::on_handshake(std::shared_ptr<WsServer::Connection>, SimpleWeb::CaseInsensitiveMultimap &) {
    std::cout<<"On handshake\n";
}

rest_server::rest_server() {
    m_g_httpHandler = new WsServer();
}






