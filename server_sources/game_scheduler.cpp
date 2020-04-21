//
// Created by stevlulz on 19/04/2020.
//

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "game_scheduler.h"
#include <boost/log/trivial.hpp>

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

boost::property_tree::ptree game_scheduler::parse_json(std::string  rec) {
    std::stringstream ss;
    ss << rec;
    pt::ptree tt;
    pt::read_json(ss, tt);
    return tt;
}

void game_scheduler::join_routine(const pt::ptree& pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"join_routine() start";
    std::string game_id = pt.get<std::string>("game_id");
    std::shared_ptr<game> tmp_game = get_game_instance(game_id);
    std::string tmp_username = pt.get<std::string>("username");
    BOOST_LOG_TRIVIAL(info)<<"join_routine -- username : "<<tmp_username<<" -- game_id : "<<game_id;

    tmp_game->add_new_player(tmp_username,p_connection);
    BOOST_LOG_TRIVIAL(info)<<"join_routine() exit";
}

void game_scheduler::creation_routine(const pt::ptree& pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"creation_routine() start";
    std::string game_id = pt.get<std::string>("game_id");
    std::shared_ptr<game> tmp_game = create_game_instance(game_id);
    std::string tmp_username = pt.get<std::string>("username");
    BOOST_LOG_TRIVIAL(info)<<"creation_routine -- username : "<<tmp_username<<" -- game_id : "<<game_id;

    tmp_game->add_new_player(tmp_username,p_connection);
    BOOST_LOG_TRIVIAL(info)<<"creation_routine() exit";
}

void game_scheduler::move_routine(const pt::ptree &pt) {
    BOOST_LOG_TRIVIAL(info)<<"move_routine() start";
    BOOST_LOG_TRIVIAL(info)<<"move::value : "<<pt.get<std::string>("value");


    BOOST_LOG_TRIVIAL(info)<<"move_routine() exit";
}

void game_scheduler::rotate_routine(const pt::ptree &pt) {
    BOOST_LOG_TRIVIAL(info)<<"rotate_routine() start";
    BOOST_LOG_TRIVIAL(info)<<"rotate::value : "<<pt.get<std::string>("value");


    BOOST_LOG_TRIVIAL(info)<<"rotate_routine() exit";
}

void game_scheduler::fire_routine(const pt::ptree &pt) {
    BOOST_LOG_TRIVIAL(info)<<"fire_routine() start";


    BOOST_LOG_TRIVIAL(info)<<"fire_routine() exit";
}

