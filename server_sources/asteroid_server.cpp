

#include <iostream>
#include <rest_server.h>
#include <game_scheduler.h>

auto main(int argc, char **argv) -> int {


    std::string port = "9999";
    std::string host = "localhost";
    std::shared_ptr<rest_server> server = rest_server::get_instance();

    server->init(host, port);

    server->run();
    std::string sid = "sidahmed";
    std::string si2 = "ssidahmed";

    game_scheduler::create_game_instance(sid);

    game_scheduler::create_game_instance(sid);

    game_scheduler::create_game_instance(si2);
    game_scheduler::create_game_instance(sid);

    game_scheduler::create_game_instance(si2);
    game_scheduler::create_game_instance(sid);

    std::shared_ptr<game> my_game = game_scheduler::get_game_instance(sid);
    return 0;
}