//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_CLIENT_MESSAGE_FACTORY_H
#define ASTEROID_CLIENT_MESSAGE_FACTORY_H

#include <string>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
class client_message_factory{
public:
    static std::string get_create_game_message(const std::string& p_username){
        pt::ptree root;

        root.put("type","create_game");
        root.put("username",p_username);
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);


        BOOST_LOG_TRIVIAL(info)<< "get_create_game_message()";
        return ss.str();
    }
    static std::string get_join_game_message(const std::string& p_game_id, const std::string& p_username){
        pt::ptree root;

        root.put("type","join_game");
        root.put("username",p_username);
        root.put("game_id",p_username);

        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);

        BOOST_LOG_TRIVIAL(info)<< "get_join_game_message()";
        return ss.str();
    }
    static std::string get_request_view_message(const std::string& p_game_id){
        //json::value o;
        //o["type"] = json::value("request_view");
        //o["username"] = json::value(p_game_id);

        //std::stringstream s;
        //s << o;
        BOOST_LOG_TRIVIAL(info)<< "get_request_view_message()";
        return "get_request_view_message";
    }
};

#endif //ASTEROID_CLIENT_MESSAGE_FACTORY_H
