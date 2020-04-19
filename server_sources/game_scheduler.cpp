//
// Created by stevlulz on 19/04/2020.
//

#include "game_scheduler.h"

std::string game_scheduler::str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
std::map<std::string,std::shared_ptr<game>> game_scheduler::m_games_instances;

std::shared_ptr<game> game_scheduler::get_game_instance(const std::string &game_id) {
    auto ret = m_games_instances.find(game_id);
    if(ret != m_games_instances.end())
        return ret->second;
    return nullptr;
}

std::shared_ptr<game> game_scheduler::create_game_instance(std::string &game_id){
    auto ret = get_game_instance(game_id);
    if (ret != nullptr){
        std::cout<<"Game with id "<<game_id<<" already exists\n";
        return nullptr;
    }
    std::shared_ptr<game> tmp = std::make_shared<game>(game(game_id));
    m_games_instances.insert(std::make_pair(game_id,tmp));

    return tmp;
}

