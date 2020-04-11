
//#include "headers/rest_client.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
int main() {

    //test with an online webservice TODO Delete
    // web::http::client::http_client client(U("https://reqres.in/api/users/1"));
    // http_response response = client.request(web::http::methods::GET).get();
    // const utility::string_t body = response.extract_string().get();
    //  std::cout<<body;
    //std::string host = "http://localhost";
    //std::string port = "19999";
    // asteroid_game::client::set_config(host,port);
    //std::shared_ptr<rest_client> e = rest_client::get_instance();
    //e->init(host,port);
    //e->run();
    http_client client(U("http://www.unistra.fr"));
    uri_builder builder(U("index.php"));
    std::cout<<client.request(methods::GET,builder.to_string()).get().to_string();
    return 0;
}
