#include "client.h"
int main(int argc, char** argv)
{
    //test with an online webservice TODO Delete
   // web::http::client::http_client client(U("https://reqres.in/api/users/1"));
   // http_response response = client.request(web::http::methods::GET).get();
   // const utility::string_t body = response.extract_string().get();
  //  std::cout<<body;
    client::start(argc,argv);

    return 0;
}
