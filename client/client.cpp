//
// Created by stevlulz on 07/04/2020.
//

#include <client.h>

void asteroid_game::client::client_gui() {
    //main thread for displaying gui

    graphiqueSDL fenetre{1000, 800};

    polyClient b1 = {
            {200, 100},
            {400, 300},
            {500, 500}
    };
    //alphaNumClient a1 {"HelloWorld!", {10,10}};
    b1.afficherSurFenetre(fenetre);
    //a1.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    getchar();
}

void asteroid_game::client::client_network_interface() {
    asteroid_game::client::on_initialize();
    std::string line;
    std::getline(std::cin, line);
    asteroid_game::client::on_shutdown();
}
void asteroid_game::client::on_shutdown()
{
    asteroid_game::client::g_httpHandler->close().wait();
}

void asteroid_game::client::on_initialize() {
        uri_builder uri(client::host+":"+client::port);
        auto addr = uri.to_uri().to_string();
        asteroid_game::client::g_httpHandler = std::make_unique<client_http_service_handler>(addr);
        asteroid_game::client::g_httpHandler->open().wait();
        std::cout<< utility::string_t(U("Client for requests at: ")) << addr << std::endl;
}

void asteroid_game::client::start(std::string &p_host, std::string &p_port) {
    asteroid_game::client::host = std::move(p_host);
    asteroid_game::client::port = std::move(p_port);
    std::thread gui(client::client_gui);
    std::thread cni(client::client_network_interface);
    gui.join();
    cni.join();
}
