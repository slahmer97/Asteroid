
#include "headers/rest_client.h"


int main() {

    //test with an online webservice TODO Delete
    // web::http::client::http_client client(U("https://reqres.in/api/users/1"));
    // http_response response = client.request(web::http::methods::GET).get();
    // const utility::string_t body = response.extract_string().get();
    //  std::cout<<body;
    std::string host = "http://localhost";
    std::string port = "9999";
    // asteroid_game::client::set_config(host,port);
    std::shared_ptr<rest_client> e = rest_client::get_instance();
    e->init(host,port);
    e->run();
    return 0;
}
