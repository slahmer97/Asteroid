
/*
void TEST() {
    game g{};
    polyServeur ps = {{1, 2},
                      {2, 2},
                      {3, 4}};
    moyenAsteroid ma = {{8, 2},
                        {2, 6},
                        {3, 7}};
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