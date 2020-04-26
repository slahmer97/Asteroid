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
        if(count == 1){
            points.emplace_back(270,240);
            points.emplace_back(240,300);
            points.emplace_back(300,300);
        }
        else if(count == 2){
            points.emplace_back(370,240);
            points.emplace_back(340,300);
            points.emplace_back(400,300);
        }
        else if(count == 3){
            points.emplace_back(570,240);
            points.emplace_back(540,300);
            points.emplace_back(600,300);
        }
        else if(count == 4){
            points.emplace_back(670,240);
            points.emplace_back(640,300);
            points.emplace_back(700,300);
        }
        count++;
        //initialize fixed point for player
        int minX = 0xFFFF, minY = 0xFFFF, maxX = 0, maxY = 0;
        for (const auto& p : points) {
            if (p.x > maxX) maxX = p.x;
            if (p.x < minX) minX = p.x;
            if (p.y > maxY) maxY = p.y;
            if (p.y < minY) minY = p.y;
        }
        this->m_center.x = (minX) + ((maxX - minX) / 2);
        this->m_center.y =  (minY )+ ((maxY - minY) / 2);
    }
    explicit vaisseau(std::vector<point> points) : polyServeur(std::move(points)) {}

    vaisseau() : polyServeur{} {
        // construire un triangle
    }

    void rotationDroite(int degree = 2) {
        BOOST_LOG_TRIVIAL(info)<<"rotationDroite() -- username : "<<m_username;
        rotate(degree);
    }

    void rotationGauche(int degree = -2) {
        BOOST_LOG_TRIVIAL(info) << "rotationGauche() -- username : " << m_username;
        rotate(degree);
    }

    void rotate(int deg){
        // placeholder
        // Shifting the pivot point to the origin
        // and the given points accordingly
        double cos_ = std::cos(deg);
        double sin_ = std::sin(deg);
        for (auto &p : points) {
            double shift_x = static_cast<double>(p.x - m_center.x);
            double shift_y = static_cast<double>(p.y - m_center.y);
            double xnew = static_cast<double>(shift_x) * cos_ - static_cast<double>(shift_y) * sin_;
            double ynew = static_cast<double>(shift_x) * sin_ + static_cast<double>(shift_y) * cos_;
            p.x = static_cast<int>(xnew + m_center.x);
            p.y = static_cast<int>(ynew + m_center.x);
        }
/*
        for (auto &p : points) {
            double dist = std::sqrt(std::pow(m_center.x-p.x,2)+std::pow(m_center.y-p.y,2));
            std::cout << "X : " << p.x << " -- Y : " << p.y << " -- Dist : "<<dist<<std::endl;
        }
        */
    }
    void avancer(const vec2d& v) {
        BOOST_LOG_TRIVIAL(info)<<"avancer() -- username : "<<m_username;

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

    inline bool is_me(std::shared_ptr<WsServer::Connection>& p_connection){
        BOOST_LOG_TRIVIAL(info)<<"is_me() -- p_con : "<<p_connection.get()<<" -- m_con : "<<m_connection.get();
        return p_connection.get() == m_connection.get();
    }

    inline const std::string& get_username() const{
        return m_username;
    }

private:
    std::string m_username;
    std::shared_ptr<WsServer::Connection> m_connection;

    static int count;
};

#endif //ASTEROID_VAISSEAU_H
