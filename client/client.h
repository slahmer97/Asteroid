//
// Created by stevlulz on 24/03/2020.
//

#ifndef ASTEROID_CLIENT_H
#define ASTEROID_CLIENT_H

#include <iostream>
#include <thread>
#include "graphiqueSDL.h"
#include "polyClient.h"
#include "client_http_service_handler.h"

namespace asteroid_game{
class client {

private:
    //shared objects here
    static void client_gui() {
        //main thread for displaying gui

        graphiqueSDL fenetre{1000, 800};

        polyClient b1 = {
                         {200, 100},
                         {400, 300},
                         {500, 500}
        };

        b1.afficherSurFenetre(fenetre);
        fenetre.afficherImage();

        getchar();
    }

    static void client_network_interface() {





    }
    static void on_initialize()
    {
        uri_builder uri(client::host+":"+client::port);


        auto addr = uri.to_uri().to_string();
        g_httpHandler = std::make_unique<client_http_service_handler>(addr);
        g_httpHandler->open().wait();

        std::cout<< utility::string_t(U("Client for requests at: ")) << addr << std::endl;

    }

public:

    static void start(int argc, char **argv) {
        argc++;
        argv++;
        std::thread gui(client::client_gui);
        std::thread cni(client::client_network_interface);

        gui.join();
        cni.join();
    }
    static void set_config(std::string& p_host, std::string& p_port){
        client::host = std::move(p_host);
        client::port = std::move(p_port);
    }
private:
    static std::string host;
    static std::string port;
    static std::unique_ptr<client_http_service_handler> g_httpHandler;

};

}
#endif //ASTEROID_CLIENT_H
