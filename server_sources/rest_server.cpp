//
// Created by stevlulz on 11/04/2020.
//

#include "rest_server.h"

#include <utility>
#include <future>
#include <boost/log/trivial.hpp>
#include <game_scheduler.h>
#include <boost/property_tree/ptree.hpp>

std::shared_ptr<rest_server> rest_server::m_rest_server;




void rest_server::init(std::string &host, std::string &port) {
    //BOOST_LOG_TRIVIAL(info)<<"init() start";

    m_g_httpHandler->config.port = std::stoi(port);

    m_g_httpHandler->endpoint["^/echo/?$"].on_message = [&](const std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::InMessage> in_message) {
        this->on_message(const_cast<std::shared_ptr<WsServer::Connection> &>(connection), std::move(in_message));
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
    //BOOST_LOG_TRIVIAL(info)<<"init() exit";

}

void rest_server::run(){
    //BOOST_LOG_TRIVIAL(info)<<"run() start";

    std::promise<unsigned short> server_port;
    std::thread server_thread([&]() {
        // Start server
        this->m_g_httpHandler->start([&server_port](unsigned short port) {
            server_port.set_value(port);
        });
    });

    std::thread broadcaster([&](){
        game_scheduler::broadcaster();
    });
    //BOOST_LOG_TRIVIAL(info)<<"server_thread() started";


    std::thread stepper([&](){
            game_scheduler::start();
    });
    std::string a;
    //std::cout<<"Enter something to exit\n";
    std::cin>>a;

}

std::shared_ptr<rest_server> rest_server::get_instance()  {
    //BOOST_LOG_TRIVIAL(info)<<"get_instance()";

    if(rest_server::m_rest_server == nullptr)
        rest_server::m_rest_server = std::make_shared<rest_server>(rest_server());
    return rest_server::m_rest_server;
}
void rest_server::on_open(const std::shared_ptr<WsServer::Connection>& connection) {
    //BOOST_LOG_TRIVIAL(info)<<"on_open()";
    //std::cout<<"On open\n";

}

void rest_server::on_message(std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::InMessage> in_message) {
    //BOOST_LOG_TRIVIAL(info)<<"on_message()";
    //std::cout<<"On message\n";
    //std::cout<<"Received : "<<in_message->string()<<"\n";

    boost::property_tree::ptree root;
    try {
        root =     game_scheduler::parse_json(in_message->string());
    }
    catch (std::exception& e){
        BOOST_LOG_TRIVIAL(info)<<e.what();
        return;
    }

    auto type = root.get<std::string>("type");
    if(type == "create_game"){
        game_scheduler::creation_routine(root,connection);
    }
    else if(type == "join_game"){
        game_scheduler::join_routine(root,connection);
    }
    else if(type == "move"){
        //BOOST_LOG_TRIVIAL(info)<<"move()";
        game_scheduler::move_routine(root,connection);
    }
    else if(type == "rotate"){
        //BOOST_LOG_TRIVIAL(info)<<"rotate()";
        game_scheduler::rotate_routine(root,connection);
    }
    else if(type == "fire"){
        //BOOST_LOG_TRIVIAL(info)<<"fire()";
        game_scheduler::fire_routine(root,connection);
    }

}

void rest_server::on_close(const std::shared_ptr<WsServer::Connection>& connection, int status, const std::string &) {
    //BOOST_LOG_TRIVIAL(info)<<"on_close()";
    //std::cout<<"On close\n";
}
void rest_server::on_handshake(std::shared_ptr<WsServer::Connection>, SimpleWeb::CaseInsensitiveMultimap &) {
    //BOOST_LOG_TRIVIAL(info)<<"on_handshake()";
    //std::cout<<"On handshake\n";
}

rest_server::rest_server() {
    //BOOST_LOG_TRIVIAL(info)<<"WsServer instance is created";
    m_g_httpHandler = new WsServer();
}






