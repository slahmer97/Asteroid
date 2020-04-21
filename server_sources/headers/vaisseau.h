//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_VAISSEAU_H
#define ASTEROID_VAISSEAU_H

#include <utility>

#include "polyServeur.h"
#include "vec2d.h"
#include <boost/log/trivial.hpp>
#include "server_ws.hpp"
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;
class vaisseau : public polyServeur {
public:
    vaisseau(std::initializer_list<point> &&liste) : polyServeur(liste) {}
    vaisseau(std::string& p_username, std::shared_ptr<WsServer::Connection>& p_connection) : m_username(p_username),m_connection((p_connection)){
        BOOST_LOG_TRIVIAL(info)<<"vaisseau() -- username : "<<m_username;

        //initialize fixed point for player

    }
    explicit vaisseau(std::vector<point> points) : polyServeur(std::move(points)) {}

    vaisseau() : polyServeur{} {
        // construire un triangle
    }

    void rotationDroite(int degree = 20) {
        BOOST_LOG_TRIVIAL(info)<<"rotationDroite()";

        // placeholder

    }

    void rotationGauche(int degree = 20) {
        BOOST_LOG_TRIVIAL(info)<<"rotationGauche()";

        // placeholder
    }

    void avancer(const vec2d& v) {
        BOOST_LOG_TRIVIAL(info)<<"avancer()";

        // placeholder
    }

    void send_message(const std::string &p_message){
        BOOST_LOG_TRIVIAL(info)<<"send_message() start";
        if (m_connection == nullptr){
            BOOST_LOG_TRIVIAL(warning)<<"trying to send message with NULL m_connection";
            return;
        }
        m_connection->send(p_message);
        BOOST_LOG_TRIVIAL(info)<<"message sent";

    }

private:
    std::string m_username;
    std::shared_ptr<WsServer::Connection> m_connection;
};

#endif //ASTEROID_VAISSEAU_H
