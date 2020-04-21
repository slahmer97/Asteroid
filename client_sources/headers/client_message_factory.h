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
    static std::string get_create_game_message(const std::string& p_username, const std::string& p_game_id){
        pt::ptree root;
        root.put("type","create_game");
        root.put("username",p_username);
        root.put("game_id",p_game_id);
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_create_game_message()";
        return ss.str();
    }
    static std::string get_join_game_message(const std::string& p_game_id, const std::string& p_username){
        pt::ptree root;
        root.put("type","join_game");
        root.put("username",p_username);
        root.put("game_id",p_game_id);
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_join_game_message()";
        return ss.str();
    }
    static std::string get_request_view_message(const std::string& p_game_id){
        BOOST_LOG_TRIVIAL(info)<< "get_request_view_message() "<<p_game_id ;
        return "get_request_view_message";
    }

    static std::string get_move_forward_message(){
        pt::ptree root;
        root.put("type","move");
        root.put("value","forward");
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_move_forward_message()";
        return ss.str();
    }
    static std::string get_move_backward_message(){
        pt::ptree root;
        root.put("type","move");
        root.put("value","backward");
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_move_backward_message()";
        return ss.str();
    }
    static std::string get_left_rotate_message(){
        pt::ptree root;
        root.put("type","rotate");
        root.put("value","left");
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_left_rotate_message()";
        return ss.str();
    }
    static std::string get_right_rotate_message(){
        pt::ptree root;
        root.put("type","rotate");
        root.put("value","right");
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_right_rotate_message()";
        return ss.str();
    }
    static std::string get_fire_message(){
        pt::ptree root;
        root.put("type","fire");
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, root);
        BOOST_LOG_TRIVIAL(info)<< "get_right_rotate_message()";
        return ss.str();
    }
};

#endif //ASTEROID_CLIENT_MESSAGE_FACTORY_H
