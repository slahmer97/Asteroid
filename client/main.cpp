
#include <SDL.h>
#include <chrono>
#include <thread>
#include "graphiqueSDL.h"
#include "affichableClient.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
int main(int argc, char** argv)
{
    //test with an online webservice TODO Delete
   // web::http::client::http_client client(U("https://reqres.in/api/users/1"));
   // http_response response = client.request(web::http::methods::GET).get();
   // const utility::string_t body = response.extract_string().get();
  //  std::cout<<body;


    graphiqueSDL fenetre{1000, 800};
    polygoneAC a1 = {{100,100}, {200, 200},{300,300},{400,400}};
    std::cout<< a1.to_string()<<std::endl;

    polygoneAC r = polygoneAC::json_to_polygoneAC(a1.to_string());
    std::cout<< r.to_string()<<std::endl;

    //std::cout<<a1.m_center.x<<" "<<a1.m_center.y<<std::endl;
   // exit(1);
    polygoneAC a2 = {{400,400}, {600, 600}};

    polygoneAC b1 = {{200,100}, {400, 300}};
    polygoneAC b2 = {{500,400}, {700, 600}};

    a1.afficherSurFenetre(fenetre);
    a2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    b1.afficherSurFenetre(fenetre);
    b2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    return 0;
}
