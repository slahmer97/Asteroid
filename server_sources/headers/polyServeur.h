//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_POLYSERVEUR_H
#define ASTEROID_POLYSERVEUR_H

#include "../../client_sources/headers/polygone.h"
#include "vec2d.h"
#include "intersection.h"


class polyServeur : public polygone {
public:
    polyServeur(std::initializer_list<point> &&liste) : polygone(liste) {}

    explicit polyServeur(std::vector<point> points) : polygone(std::move(points)) {}

    std::string to_string() const {
        /*
        json::value o;
        std::vector<json::value> a{};
        for (const auto &p : points) {
            json::value tmp;
            tmp["x"] = json::value(p.x);
            tmp["y"] = json::value(p.y);
            a.emplace_back(tmp);
        }

        o["points"] = json::value::array(a);
        o["type"] = json::value(std::string("polygone"));
   */

        return "sqd";
    }

    static polyServeur json_to_polygone(const std::string& p_object) {
    /*
        json::array obj = json::value::parse(p_object)["points"].as_array();
        // unsigned long size = obj.size();
        //initialize vector with size
        for (auto &o : obj)
            res.emplace_back(o["x"].as_integer(), o["y"].as_integer());
            */
        std::vector<point> res;

        return polyServeur(res);
    }

    bool intersecte(const polyServeur &ps) const {
        intersection<point> coupe;
        bool b = false;
        for (unsigned i = 0; i < points.size() - 1; ++i)
            for (unsigned j = 0; j < ps.points.size() - 1; ++j)
                if (coupe(points[i], points[i + 1], ps.points[j], ps.points[j + 1])) {
                    b = true;
                    goto finBoucles;
                }
        finBoucles:
        return b;
    }

private:
    vec2d direction; //vecteur de direction et de velocite a implementer !!!

};

#endif //ASTEROID_POLYSERVEUR_H
