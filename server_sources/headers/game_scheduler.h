//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_GAME_SCHEDULER_H
#define ASTEROID_GAME_SCHEDULER_H

#include <iostream>
#include <map>
#include <random>
#include <algorithm>
#include <memory>
#include "game.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Game;

namespace pt = boost::property_tree;

class game_scheduler{
public:

    static std::string gen_next_id(){
        std::random_device rd;
        std::mt19937 generator(rd());
        std::string ret;
      /*  do {
            std::shuffle(str.begin(), str.end(), generator);
            ret = str.substr(10, 10);
        }while (m_games_instances.find(ret) != m_games_instances.end());
*/
        return ret;
    }

    static std::shared_ptr<game> get_game_instance(const std::string& game_id);
    static std::shared_ptr<game> create_game_instance(std::string& game_id);
    static void join_routine(const pt::ptree& pt);
    static void creation_routine(const pt::ptree& pt);
    static boost::property_tree::ptree parse_json(std::string rec);

private:
    static std::map<std::string,std::shared_ptr<game>> m_games_instances;

    static std::string str;
};

#endif //ASTEROID_GAME_SCHEDULER_H
