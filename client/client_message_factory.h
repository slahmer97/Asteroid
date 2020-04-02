//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_CLIENT_MESSAGE_FACTORY_H
#define ASTEROID_CLIENT_MESSAGE_FACTORY_H

#include <string>

class client_message_factory{
public:
    static std::string get_create_game_message(const std::string& p_username){
        return std::string("create_game_message");
    }
    static std::string get_join_game_message(const std::string& p_game_id, const std::string& p_username){
        return std::string("join_game_message");
    }
};

#endif //ASTEROID_CLIENT_MESSAGE_FACTORY_H
