
#include <rest_client.h>
#include <boost/log/trivial.hpp>


int main() {

    std::string host = "localhost";
    std::string port = "9999";
    std::shared_ptr<rest_client> e = rest_client::get_instance();
    e->init(host,port);
    e->run();

    return 0;
}
