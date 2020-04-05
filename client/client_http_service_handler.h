//
// Created by stevlulz on 05/04/2020.
//

#ifndef ASTEROID_CLIENT_HTTP_SERVICE_HANDLER_H
#define ASTEROID_CLIENT_HTTP_SERVICE_HANDLER_H
#include <iostream>
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/json.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"
using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class client_http_service_handler
{
public:
    client_http_service_handler() = default;
    inline explicit client_http_service_handler(const utility::string_t& url) : m_listener(url){
        m_listener.support(methods::POST, std::bind(&client_http_service_handler::handle_post, this, std::placeholders::_1));
    }
    ~client_http_service_handler() = default;

    inline pplx::task<void>open(){return m_listener.open();}
    inline pplx::task<void>close(){return m_listener.close();}

protected:

private:

    inline void handle_post(const http_request& message){
        std::cout<<"[Info] Post_request :"<<std::endl;

        std::cout <<  message.to_string() << endl;
        string rep = U("write post handler");
        message.reply(status_codes::OK,rep);
    }
    inline void handle_error(pplx::task<void>& t){
        try
        {
            t.get();
        }
        catch(...)
        {
            // maybe log error
        }
    }
    http_listener m_listener;
};

#endif //ASTEROID_CLIENT_HTTP_SERVICE_HANDLER_H
