//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_POLYSERVEUR_H
#define ASTEROID_POLYSERVEUR_H

#include <cpprest/http_client.h>
#include "point.h"
#include "polygone.h"

using namespace web;

class polyServeur : public polygone {
public:
    polyServeur(std::initializer_list<point>&& liste): polygone(liste) {}
    explicit polyServeur(std::vector<point> points): polygone(std::move(points)) {}

    std::string to_string() {
        json::value o;
        std::vector<json::value> a{};
        for(const auto& p : points){
            json::value tmp;
            tmp["x"] = json::value(p.x);
            tmp["y"] = json::value(p.y);
            a.emplace_back(tmp);
        }

        o["points"] = json::value::array(a);
        o["type"] = json::value(std::string("polygone"));

        std::stringstream s;
        s << o;
        return s.str();
    }

    static polyServeur json_to_polygone(const std::string& p_object) {

        json::array obj = json::value::parse(p_object)["points"].as_array();
        // unsigned long size = obj.size();
        std::vector<point> res;
        //initialize vector with size
        for (auto& o : obj)
            res.emplace_back(o["x"].as_integer(),o["y"].as_integer());
        return polyServeur(res);
    }

};

#endif //ASTEROID_POLYSERVEUR_H
