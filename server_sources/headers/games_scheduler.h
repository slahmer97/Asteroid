//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_GAME_SCHEDULER_H
#define ASTEROID_GAME_SCHEDULER_H

#include <iostream>
#include <map>
#include <random>
#include <algorithm>
#include "game.h"

class games_scheduler{
public:
    games_scheduler() = default;

    std::string gen_next_id(){
            std::random_device rd;
            std::mt19937 generator(rd());
            std::string ret;
            do {
                std::shuffle(str.begin(), str.end(), generator);
                ret = str.substr(10, 10);
            }while (m_games_instances.find(ret) != m_games_instances.end());

            return ret;
    }

private:
    std::map<std::string,game*> m_games_instances;

    static std::string str;
};
#endif //ASTEROID_GAME_SCHEDULER_H
std::string games_scheduler::str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";