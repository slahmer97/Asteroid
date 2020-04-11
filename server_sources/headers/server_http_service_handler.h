//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_SERVER_HTTP_SERVICE_HANDLER_H
#define ASTEROID_SERVER_HTTP_SERVICE_HANDLER_H
#include <iostream>

#include "stdafx.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class server_http_service_handler
{
public:
    server_http_service_handler() = default;
    inline explicit server_http_service_handler(const utility::string_t& url) : m_listener(url){
        m_listener.support(methods::GET, std::bind(&server_http_service_handler::handle_get, this, std::placeholders::_1));
        m_listener.support(methods::PUT, std::bind(&server_http_service_handler::handle_put, this, std::placeholders::_1));
        m_listener.support(methods::POST, std::bind(&server_http_service_handler::handle_post, this, std::placeholders::_1));
        m_listener.support(methods::DEL, std::bind(&server_http_service_handler::handle_delete, this, std::placeholders::_1));
    }
    ~server_http_service_handler() = default;

    inline pplx::task<void>open(){return m_listener.open();}
    inline pplx::task<void>close(){return m_listener.close();}

protected:

private:
    inline void handle_get(const http_request& message){
        std::cout<<"[Info] Get_request :"<<std::endl;
        std::cout <<  message.to_string() << endl;

        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        std::cout<<"Relative uri : "<<message.relative_uri().to_string()<<"\n";
        string rep = U("write post handler");

        message.reply(status_codes::OK,rep);
    }
    inline void handle_put(const http_request& message){
        std::cout<<"[Info] Put_request :"<<std::endl;

        std::cout <<  message.to_string() << endl;
        string rep = U("write post handler");
        message.reply(status_codes::OK,rep);
    }
    inline void handle_post(const http_request& message){
        std::cout<<"[Info] Post_request :"<<std::endl;

        std::cout <<  message.to_string() << endl;
        string rep = U("write post handler");
        message.reply(status_codes::OK,rep);
    }
    inline void handle_delete(const http_request& message){
        std::cout<<"[Info] Delete_request :"<<std::endl;
        std::cout <<  message.to_string() << endl;

        string rep = U("write delete handler");
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

#endif //ASTEROID_SERVER_HTTP_SERVICE_HANDLER_H
