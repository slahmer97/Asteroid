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
#include "grandAsteroid.h"
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
class game {
public:

    explicit game(std::string& game_id) : m_game_id{game_id}, score{},
                                        asteroids{}, lasers{}, vaisseaux{}
    {

    }

    void start() {
        BOOST_LOG_TRIVIAL(info)<<"start() game_id : "<<m_game_id;

        for (int i = 0; i < 10; ++i)
            asteroids.emplace_back(new grandAsteroid{});
    }

    void run() {
        for (auto& i : asteroids)
            i->step();
        for (int i = 0; i < lasers.size(); ++i)
        {
            if (lasers[i]->isBordure()) lasers.erase(lasers.begin() + i);
            else lasers[i]->step();
        }
        for (auto& i : vaisseaux) // pour faire passer les vaiseaux de l'autre coter
            i->step();
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
        player->avancer({});
        BOOST_LOG_TRIVIAL(info)<<"move_forward() -- end --  username : "<<player->get_username();
    }
    inline void move_backward(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- start -- username : "<<player->get_username();
        player->avancer({});
        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();
    }
    inline void rotate_left(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"rotate_left() -- start -- username : "<<player->get_username();
        player->rotationGauche(-10.0);
        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();

    }
    inline void rotate_right(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"rotate_right() --start -- username : "<<player->get_username();
        player->rotationDroite(10.0);
        BOOST_LOG_TRIVIAL(info)<<"move_backward() -- end -- username : "<<player->get_username();
    }
    inline void fire(std::shared_ptr<vaisseau>& player){
        BOOST_LOG_TRIVIAL(info)<<"fire() -- start -- username : "<<player->get_username();
        vec2d from = player->points[0];
        vec2d to = (player->points[0]-player->m_center).normalize()*10+from;
        auto* l = new laser(to,from);
        if(l != nullptr)
            lasers.emplace_back(l);
        else
            BOOST_LOG_TRIVIAL(info)<<"NULL LASER"<<player->get_username();
        BOOST_LOG_TRIVIAL(info)<<"fire() -- end -- username : "<<player->get_username();
    }
    inline void broadcast_view(){
        std::string view = get_game_view();
        BOOST_LOG_TRIVIAL(info)<<"broadcast_view() \n";//<<view;
        for(const auto& p : vaisseaux)
            p->send_message(view);
    }
private:

    inline std::string get_game_view(){
        pt::ptree root;
        pt::ptree shapes;
        for(const auto & shape : asteroids){
            pt::ptree child = shape->to_ptree();
            shapes.push_back(std::make_pair("",std::move(child)));
        }
        for(const auto& shape : vaisseaux){
            pt::ptree child = shape->to_ptree();
            shapes.push_back(std::make_pair("",std::move(child)));
        }
        for(const auto& shape : lasers){
            pt::ptree child = shape->to_ptree();
            shapes.push_back(std::make_pair("",std::move(child)));
        }
        root.put("type","game_view");
        root.add_child("shapes",shapes);
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);

        return ss.str();
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
