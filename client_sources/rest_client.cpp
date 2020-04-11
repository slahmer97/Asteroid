//
// Created by stevlulz on 08/04/2020.
//

#include <cpprest/details/basic_types.h>
#include <thread>
#include <cpprest/http_client.h>
#include "headers/rest_client.h"
#include "headers/graphiqueSDL.h"
#include "headers/polyClient.h"
#include "headers/client_http_service_handler.h"
#include "headers/alphaNumClient.h"

std::shared_ptr<rest_client> rest_client::s_rest_client;


void rest_client::init(std::string &host, std::string &port) {
    if(m_g_httpHandler != nullptr){
        std::cerr<<"[!] client is already initialized \n";
        return;
    }
    uri_builder uri(host+":"+port);
    m_uri = uri.to_uri().to_string();
    on_initialize();
}

void rest_client::on_shutdown()
{
    m_g_httpHandler->close().wait();
    std::cout<<"[+] Client rest shutdown\n";
}

void rest_client::on_initialize() {

    m_g_httpHandler = std::make_unique<client_http_service_handler>(m_uri);
    std::cout<<"[+] client rest was successfully initialized\n";

}

void rest_client::client_network()  {
    m_g_httpHandler->open().wait();
    std::cout<<"client network interface is running on : "<<m_uri<<"\n";
}

void rest_client::client_gui(){
    //main thread for displaying gui
    std::cout<<"client gui is started : "<<"\n";


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
}


void rest_client::run() {
    std::thread gui([&]() {
        this->client_gui();
    });

    std::thread net([&]() {
        this->client_network();
    });

    gui.join();


    net.join();

    on_shutdown();
}

std::shared_ptr<rest_client > rest_client::get_instance() noexcept {
    if (rest_client::s_rest_client == nullptr){
        rest_client::s_rest_client = std::make_shared<rest_client>(rest_client());
    }
    return rest_client::s_rest_client;
}


