

#include <iostream>
#include <polyServeur.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <rest_server.h>
#include <game.h>

namespace pt = boost::property_tree;
auto main(int argc, char **argv) -> int {

    std::string port = "9999";
    std::string host = "localhost";
    std::shared_ptr<rest_server> server = rest_server::get_instance();

    server->init(host, port);
    std::cout << "The game server is up and running!" << std::endl;
    server->run();
/*
    std::shared_ptr<WsServer::Connection> c = std::make_shared<WsServer::Connection>(nullptr);

    vaisseau v(port,c );
    for(auto& p : v.points)
        p.print();
    std::cout<<"------------------------------------\n";

    int i = 180;
    for (int j = 0; j <90 ; ++j) {
        v.rotationDroite();
        for(auto& p : v.points)
            p.print();
        std::cout<<"______________________________________________\n";
    }
    std::cout<<"------------------------------------\n";
    for(auto& p : v.points)
        p.print();
*/
    return 0;
}