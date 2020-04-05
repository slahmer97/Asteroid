//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_CLIENT_MESSAGE_FACTORY_H
#define ASTEROID_CLIENT_MESSAGE_FACTORY_H

#include <string>
#include <cpprest/http_client.h>


using namespace web;
class client_message_factory{
public:
    static std::string get_create_game_message(const std::string& p_username){
        json::value o;
        o["type"] = json::value("create_game");
        o["username"] = json::value(p_username);

        std::stringstream s;
        s << o;
        return s.str();
    }
    static std::string get_join_game_message(const std::string& p_game_id, const std::string& p_username){
        json::value o;
        o["type"] = json::value("join_game");
        o["username"] = json::value(p_username);
        o["game_id"] = json::value(p_game_id);
        o["server_ip"] = json::value("localhost");
        o["server_port"] = json::value("99992");
        std::stringstream s;
        s << o;
        return s.str();
    }
    static std::string get_request_view_message(const std::string& p_game_id){
        json::value o;
        o["type"] = json::value("request_view");
        o["username"] = json::value(p_game_id);

        std::stringstream s;
        s << o;
        return s.str();
    }
};

#endif //ASTEROID_CLIENT_MESSAGE_FACTORY_H
