#include "headers/games_scheduler.h"
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

#include <memory>
#include "headers/server_http_service_handler.h"


using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


std::unique_ptr<server_http_service_handler> g_httpHandler;

void on_initialize(const string_t& address)
{
    uri_builder uri(address);


    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::make_unique<server_http_service_handler>(addr);
    g_httpHandler->open().wait();

    std::cout<< utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

}


void on_shutdown()
{
    g_httpHandler->close().wait();
}

auto main(int argc,char**argv) -> int {

    utility::string_t port = U("9999");
    if(argc == 2)
    {
        port = argv[1];
    }

    utility::string_t address = U("http://localhost");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}