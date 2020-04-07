//
// Created by stevlulz on 24/03/2020.
//

#ifndef ASTEROID_CLIENT_H
#define ASTEROID_CLIENT_H

#include <iostream>
#include <thread>
#include "graphiqueSDL.h"
#include "polyClient.h"
#include "alphaNumClient.h"
#include "client_http_service_handler.h"

namespace asteroid_game{
class client {

private:
    //shared objects here
    inline static void client_gui();
    inline static void client_network_interface();

    static void on_shutdown();


     static void on_initialize();
public:

     static void start(std::string& p_host, std::string& p_port);
    //inline static void set_config(std::string& p_host, std::string& p_port){

    //}
private:
    static std::string host;
    static std::string port;
    static std::unique_ptr<client_http_service_handler> g_httpHandler;

};

}
#endif //ASTEROID_CLIENT_H
