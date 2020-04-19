<<<<<<< HEAD
=======
#include "headers/games_scheduler.h"
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

#include <memory>
#include <rest_server.h>
#include "headers/server_http_service_handler.h"
#include "headers/polyServeur.h"
#include "headers/moyenAsteroid.h"
#include "headers/intersection.h"
>>>>>>> cdb65411f1a28e9423c5e723495e0ab226ec918f

/*
void TEST() {
    game g{};

    moyenAsteroid ma = {{8, 2}, {2, 6}, {3, 7}};

    point p1 = {1, 1}, p2 = {2, 3}, p3 = {3, 1};
    point q1 = {2, 2}, q2 = {4, 5}, q3 = {4, 2};
    polyServeur psA = {p1, p2, p3, p1};
    polyServeur psB = {q1, q2, q3, q1};
    psA.intersecte(psB) ? std::cout << "Oui\n" : std::cout << "Non\n";
}
*/
#include <iostream>
#include <rest_server.h>

auto main(int argc, char **argv) -> int {


    std::string port = "9999";
    std::string host = "localhost";
    std::shared_ptr<rest_server> server = rest_server::get_instance();

    server->init(host, port);

    server->run();
    return 0;
}