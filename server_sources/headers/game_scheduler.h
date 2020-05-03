
#ifndef ASTEROID_GAME_SCHEDULER_H
#define ASTEROID_GAME_SCHEDULER_H

#include <map>
#include <memory>
#include "game.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "server_ws.hpp"

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

namespace pt = boost::property_tree;

class game_scheduler {
public:

    static std::shared_ptr<game> get_game_instance(const std::string &game_id);

    static std::shared_ptr<game> create_game_instance(std::string &game_id);

    static void join_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection> p_connection);

    static void creation_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection> p_connection);

    static void move_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection> p_connection);

    static void rotate_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection> p_connection);

    static void fire_routine(const pt::ptree &pt, std::shared_ptr<WsServer::Connection> p_connection);

    static boost::property_tree::ptree parse_json(std::string rec);

    static void broadcaster();

    static std::shared_ptr<vaisseau> get_player_by_connection(std::shared_ptr<WsServer::Connection> p_connection);

    static std::shared_ptr<game> get_game_by_player_connection(std::shared_ptr<WsServer::Connection> p_connection);

    static void start();

private:
    static std::map<std::string, std::shared_ptr<game>> m_games_instances;
    static std::string str;
};

#endif //ASTEROID_GAME_SCHEDULER_H
