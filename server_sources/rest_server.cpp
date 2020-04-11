//
// Created by stevlulz on 11/04/2020.
//

#include "rest_server.h"
std::shared_ptr<rest_server> rest_server::m_rest_server;
void rest_server::on_initialize() {
    m_g_httpHandler = std::make_unique<server_http_service_handler>(m_uri);
    std::cout<<"[+] client rest was successfully initialized\n";
}

void rest_server::on_shutdown() {
        m_g_httpHandler->close().wait();
        std::cout<<"[+] Server rest shutdown\n";
}

void rest_server::init(std::string &host, std::string &port) {
    if(m_g_httpHandler != nullptr){
        std::cerr<<"[!] client is already initialized \n";
        return;
    }
    uri_builder uri(host+":"+port);
    m_uri = uri.to_uri().to_string();
    on_initialize();
}

void rest_server::run(){
    m_g_httpHandler->open().wait();
    std::cout<<"Server network interface is running on : "<<m_uri<<"\n";


    std::string a;
    std::cout<<"Enter something to exit\n";
    std::cin>>a;

}

std::shared_ptr<rest_server> rest_server::get_instance()  {
    if(rest_server::m_rest_server == nullptr)
        rest_server::m_rest_server = std::make_shared<rest_server>(rest_server());
    return rest_server::m_rest_server;
}


