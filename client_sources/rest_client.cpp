//
// Created by stevlulz on 08/04/2020.
//

#include <thread>
#include <client_message_factory.h>
#include "headers/rest_client.h"
#include "headers/graphiqueSDL.h"
#include "headers/polyClient.h"
#include "headers/client_http_service_handler.h"
#include "headers/alphaNumClient.h"
#include <boost/log/trivial.hpp>

std::shared_ptr<rest_client> rest_client::s_rest_client;


void rest_client::init(std::string &host, std::string &port) {
    BOOST_LOG_TRIVIAL(info)<<"init() start";
    m_uri = std::string(host)+std::string(":")+std::string(port)+std::string("/echo");
    BOOST_LOG_TRIVIAL(info)<<"init() uri is created : "<<m_uri;
    BOOST_LOG_TRIVIAL(info)<<"init() exit";

}


void rest_client::client_network()  {
    BOOST_LOG_TRIVIAL(info)<<"client_network() init "<<m_uri;
    m_g_httpHandler = new WsClient(m_uri);
    m_g_httpHandler->on_message = [&](const std::shared_ptr<WsClient::Connection>& connection, const std::shared_ptr<WsClient::InMessage> &in_message) {
        this->on_message(connection,in_message);
    };

    m_g_httpHandler->on_open = [&](const std::shared_ptr<WsClient::Connection>& connection) {
        this->on_open(const_cast<std::shared_ptr<WsClient::Connection> &>(connection));
    };

    m_g_httpHandler->on_close = [&](const std::shared_ptr<WsClient::Connection>& connection, int status, const std::string & reason) {
        this->on_close(connection,status,reason);
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    m_g_httpHandler->on_error = [&](const std::shared_ptr<WsClient::Connection>& connection, const SimpleWeb::error_code &ec) {
        this->on_error(connection,ec);
    };

    m_g_httpHandler->start();
    BOOST_LOG_TRIVIAL(info)<<"client network interface is running on : "<<m_uri;
}

void rest_client::client_gui(){
    //main thread for displaying gui
    //BOOST_LOG_TRIVIAL(info)<<"Client gui is started";
    BOOST_LOG_TRIVIAL(info)<<"client_gui() started";


    graphiqueSDL fenetre{1000, 800};
    polyClient b1 = {
            {200, 100},
            {400, 300},
            {500, 500}
    };
    alphaNumClient a1 {"HelloWorld, le retour ! Score : 19999", {10,10}};
    b1.afficherSurFenetre(fenetre);
    a1.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    getchar();
    BOOST_LOG_TRIVIAL(info)<<"client_gui() ended";
}


void rest_client::run() {
    std::thread gui([&]() {
        BOOST_LOG_TRIVIAL(info)<<"gui thread started";
        //this->client_gui();
    });
    std::thread net([&]() {
        BOOST_LOG_TRIVIAL(info)<<"network thread started";
        this->client_network();
    });


    gui.join();
    sleep(8);
    send_create_game_message();
    send_move_forward_message();
    send_move_backward_message();
    send_rotate_left_message();
    send_rotate_right_message();
    send_fire_message();
    send_fire_message();
    send_rotate_left_message();
    send_move_forward_message();
    send_rotate_right_message();
    send_fire_message();

    // net.join();
   // send_create_game_message();
}

std::shared_ptr<rest_client > rest_client::get_instance() noexcept {
    if (rest_client::s_rest_client == nullptr){
        rest_client::s_rest_client = std::make_shared<rest_client>(rest_client());
        BOOST_LOG_TRIVIAL(info)<<"rest client instance is being created";
    }
    else{
        BOOST_LOG_TRIVIAL(warning)<<"rest client instance already exist";
    }
    return rest_client::s_rest_client;
}

void rest_client::send_create_game_message(){
    BOOST_LOG_TRIVIAL(info)<<"send_create_game_message()";
    std::string payload = client_message_factory::get_create_game_message("stevlulz","game_123");

    std::string ret = send_message(payload);

    BOOST_LOG_TRIVIAL(info)<<"Reiceived : "<<ret;
}

std::string rest_client::send_message(const std::string &message){
    if(this->m_connection == nullptr){
        BOOST_LOG_TRIVIAL(fatal)<<"Attempting to send message without specifiying server connection";
        throw std::runtime_error("server connection is null");
    }
    m_connection->send(message);
    return "DONE";
}





void rest_client::on_open(std::shared_ptr<WsClient::Connection>& connection){
    BOOST_LOG_TRIVIAL(info)<<"on_open() start";

    //connection->send("Hello server");
    this->m_connection = connection;
    BOOST_LOG_TRIVIAL(info)<<"on_open() end";

}
void rest_client::on_message(const std::shared_ptr<WsClient::Connection>& connection,const std::shared_ptr<WsClient::InMessage>& in_message){
    BOOST_LOG_TRIVIAL(info)<<"on_message() start";


    BOOST_LOG_TRIVIAL(info)<<"on_message() end";
}

void rest_client::on_error(const std::shared_ptr<WsClient::Connection> &connection, const SimpleWeb::error_code &ec) {
    BOOST_LOG_TRIVIAL(info)<<"on_error() start";


    BOOST_LOG_TRIVIAL(info)<<"on_error() end";
}

void rest_client::on_close(const std::shared_ptr<WsClient::Connection> &connection, int status, const std::string &reason) {
    BOOST_LOG_TRIVIAL(info)<<"on_close() start";


    BOOST_LOG_TRIVIAL(info)<<"on_close() end";
}

void rest_client::send_move_forward_message() {
    std::string msg = client_message_factory::get_move_forward_message();
    send_message(msg);
}

void rest_client::send_move_backward_message() {
    std::string msg = client_message_factory::get_move_backward_message();
    send_message(msg);
}

void rest_client::send_rotate_left_message() {
    std::string msg = client_message_factory::get_left_rotate_message();
    send_message(msg);
}

void rest_client::send_rotate_right_message() {
    std::string msg = client_message_factory::get_right_rotate_message();
    send_message(msg);
}

void rest_client::send_fire_message() {
    std::string msg = client_message_factory::get_fire_message();
    send_message(msg);
}

