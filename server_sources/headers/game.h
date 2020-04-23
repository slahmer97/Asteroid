//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_GAME_H
#define ASTEROID_GAME_H

#include <iostream>
#include <utility>
#include "asteroid.h"
#include "laser.h"
#include "vaisseau.h"

class game {
public:

    explicit game(std::string& game_id) : m_game_id{game_id}, score{},
                                        asteroids{}, lasers{}, vaisseaux{}
    {}

    void start() {
        BOOST_LOG_TRIVIAL(info)<<"start() game_id : "<<m_game_id;

    }

    void add_new_player(std::string& p_username,std::shared_ptr<WsServer::Connection>& p_connection){
        std::shared_ptr<vaisseau> tmp = std::make_shared<vaisseau>(vaisseau(p_username,p_connection));
        vaisseaux.push_back(tmp);
        start();
    }
    std::shared_ptr<vaisseau> has_player(std::shared_ptr<WsServer::Connection>& p_connection){
        for(const auto& v : vaisseaux)
            if(v->is_me(p_connection))
                return v;
        return nullptr;
    }

    inline void move_forward(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"move_forward() -- start  username : "<<player->get_username();

        BOOST_LOG_TRIVIAL(info)<<"move_forward() -- end --  username : "<<player->get_username();
    }
    inline void move_backward(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- start -- username : "<<player->get_username();

        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();
    }
    inline void rotate_left(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"rotate_left() -- start -- username : "<<player->get_username();


        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();

    }
    inline void rotate_right(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"rotate_right() --start -- username : "<<player->get_username();


        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();
    }
    inline void fire(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"fire() -- start -- username : "<<player->get_username();

        BOOST_LOG_TRIVIAL(info)<<"fire() -- end -- username : "<<player->get_username();
    }
private:
    std::string m_game_id;
    int score;
    std::vector<std::shared_ptr<asteroid>> asteroids;
    std::vector<std::shared_ptr<laser>> lasers;
    std::vector<std::shared_ptr<vaisseau>> vaisseaux;
    // autre, placeholder
};

#endif //ASTEROID_GAME_H
