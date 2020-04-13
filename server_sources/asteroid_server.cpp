#include "headers/games_scheduler.h"
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

#include <memory>
#include <rest_server.h>
#include "headers/server_http_service_handler.h"
#include "headers/polyServeur.h"
#include "headers/moyenAsteroid.h"
#include "headers/intersection.h"

void TEST() {
    game g{};

    polyServeur ps = {{1, 2},
                      {2, 2},
                      {3, 4}};

    moyenAsteroid ma = {{8, 2},
                        {2, 6},
                        {3, 7}};

    intersection<point> coupe{};
    point p1 = {1, 0}, q1 = {1, 3};
    point p2 = {1, 2}, q2 = {1, 4};
    coupe(p1, q1, p2, q2) ? std::cout << "Oui\n" : std::cout << "Non\n";
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