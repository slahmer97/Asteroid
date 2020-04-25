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
    if(tmp_game == nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"attempting to join game with an unexisting game";
        std::string err = "{\"type\":\"error\",\"value\":\"game_id_does_not_exist\"}";
        p_connection->send(err);
        return;
    }
    std::shared_ptr<vaisseau> tmp_player = get_player_by_connection(p_connection);
    if(tmp_player != nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"attempting to join game with an existing player instance";
        std::string err = "{\"type\":\"error\",\"value\":\"player_already_exists\"}";
        p_connection->send(err);
        return;
    }
    std::string tmp_username = pt.get<std::string>("username");
    BOOST_LOG_TRIVIAL(info)<<"join_routine -- username : "<<tmp_username<<" -- game_id : "<<game_id;

    tmp_game->add_new_player(tmp_username,p_connection);
    BOOST_LOG_TRIVIAL(info)<<"join_routine() exit";
}

void game_scheduler::creation_routine(const pt::ptree& pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"creation_routine() start";
    auto game_id = pt.get<std::string>("game_id");
    std::shared_ptr<game> tmp_game = create_game_instance(game_id);
    if(tmp_game == nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"attempting to create game with an existing";
        std::string err = "{\"type\" : \"error\",\"value\":\"game_id_exists\"}";
        p_connection->send(err);
        return;
    }
    std::shared_ptr<vaisseau> tmp_player = get_player_by_connection(p_connection);
    if(tmp_player != nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"attempting to create game with an existing player instance";
        std::string err = "{\"type\":\"error\",\"value\":\"player_already_joint_in_other_game\"}";
        p_connection->send(err);
        return;
    }
    std::string tmp_username = pt.get<std::string>("username");
    BOOST_LOG_TRIVIAL(info)<<"creation_routine -- username : "<<tmp_username<<" -- game_id : "<<game_id;

    tmp_game->add_new_player(tmp_username,p_connection);
    BOOST_LOG_TRIVIAL(info)<<"creation_routine() exit";
}

void game_scheduler::move_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"move_routine() start";
    std::string val = pt.get<std::string>("value");
    BOOST_LOG_TRIVIAL(info)<<"move::value : "<<val;
    std::shared_ptr<game> game = get_game_by_player_connection(p_connection);
    std::shared_ptr<vaisseau> player = get_player_by_connection(p_connection);
    if(player == nullptr || game == nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"rotate_routine() player or game instance is null";
        return;
    }
    if(val == "forward"){
        game->move_forward(player);
    }
    else if(val == "backward"){
        game->move_forward(player);
    }
    else{
        BOOST_LOG_TRIVIAL(warning)<<"move() unknown -- val :  "<<val<<" -- player : "<<player->get_username();
    }
    BOOST_LOG_TRIVIAL(info)<<"move_routine() exit";
}

void game_scheduler::rotate_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"rotate_routine() start";
    std::string val = pt.get<std::string>("value");
    BOOST_LOG_TRIVIAL(info)<<"rotate::value : "<<val;
    std::shared_ptr<game> game = get_game_by_player_connection(p_connection);
    std::shared_ptr<vaisseau> player = get_player_by_connection(p_connection);
    if(player == nullptr || game == nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"rotate_routine() player or game instance is null";
        return;
    }
    if(val == "left"){
        game->rotate_left(player);
    }
    else if(val == "right"){
        game->rotate_right(player);
    }
    else{
        BOOST_LOG_TRIVIAL(warning)<<"rotate() unknown -- val :  "<<val<<" -- player : "<<player->get_username();
    }
    BOOST_LOG_TRIVIAL(info)<<"rotate_routine() exit";
}

void game_scheduler::fire_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"fire_routine() start";
    std::shared_ptr<game> game = get_game_by_player_connection(p_connection);
    std::shared_ptr<vaisseau> player = get_player_by_connection(p_connection);
    if(player == nullptr || game == nullptr){
        BOOST_LOG_TRIVIAL(warning)<<"rotate_routine() player or game instance is null";
        return;
    }
    game->fire(player);
    BOOST_LOG_TRIVIAL(info)<<"fire_routine() exit";
}

std::shared_ptr<vaisseau> game_scheduler::get_player_by_connection(std::shared_ptr<WsServer::Connection>& p_connection){
    BOOST_LOG_TRIVIAL(info)<<"get_player_by_connection() start";
    for(const auto& game : m_games_instances){
        const auto& p = game.second->has_player(p_connection);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

std::shared_ptr<game> game_scheduler::get_game_by_player_connection(std::shared_ptr<WsServer::Connection>& p_connection) {
    BOOST_LOG_TRIVIAL(info)<<"get_game_by_player_connection() start";
    for(const auto& game : m_games_instances){
        const auto& p = game.second->has_player(p_connection);
        if (p != nullptr)
            return game.second;
    }
    return nullptr;
}

void game_scheduler::broadcaster() {

    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for(const auto& game : m_games_instances)
            game.second->broadcast_view();
    }

}

