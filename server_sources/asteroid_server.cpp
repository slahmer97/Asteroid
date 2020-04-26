

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
    server->run();
/*
    std::shared_ptr<WsServer::Connection> c = std::make_shared<WsServer::Connection>(nullptr);

    vaisseau v(port,c );
    int i = 10;
    while(i-- > -10)
        v.rotationGauche();
   */
    return 0;
}