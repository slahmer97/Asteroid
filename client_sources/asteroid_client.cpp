
//#include "headers/rest_client.h"


#include <rest_client.h>


#include <boost/log/trivial.hpp>


int main() {

    //test with an online webservice TODO Delete

    //  std::cout<<body;
    std::string host = "localhost";
    std::string port = "9999";
    // asteroid_game::client::set_config(host,port);
    std::shared_ptr<rest_client> e = rest_client::get_instance();
    e->init(host,port);
    e->run();
    //web::http::client::http_client client(U("http://date.jsontest.com/"));
    //http_response response = client.request(web::http::methods::GET).get();
    //const pplx::task<string_t> body = response.extract_string();
    // Open stream to output file.

    std::cout<<"Hello world\n";




    return 0;
}
