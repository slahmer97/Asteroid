#include "headers/games_scheduler.h"
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

#include <memory>
#include <rest_server.h>
#include "headers/server_http_service_handler.h"



auto main(int argc,char**argv) -> int {

    utility::string_t port = U("9999");
    if(argc == 2)
    {
        port = argv[1];
    }
    std::shared_ptr<rest_server> server = rest_server::get_instance();
    utility::string_t host = "http://localhost";
    server->init(host, port);

    server->run();
    return 0;
}