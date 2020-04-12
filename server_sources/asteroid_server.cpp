#include "headers/games_scheduler.h"
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

#include <memory>
#include <rest_server.h>
#include "headers/server_http_service_handler.h"
#include "headers/polyServeur.h"
#include "headers/moyenAsteroid.h"

void TEST() {
    game g{};
    polyServeur ps = {{1, 2},
                      {2, 2},
                      {3, 4}};
    moyenAsteroid ma = {{8, 2},
                        {2, 6},
                        {3, 7}};
}

auto main(int argc, char **argv) -> int {

    TEST();

    utility::string_t port = U("9999");
    if (argc == 2) {
        port = argv[1];
    }
    std::shared_ptr<rest_server> server = rest_server::get_instance();
    utility::string_t host = "http://localhost";
    server->init(host, port);

    server->run();
    return 0;
}