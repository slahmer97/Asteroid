//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_POLYSERVEUR_H
#define ASTEROID_POLYSERVEUR_H

#include "../../client_sources/headers/polygone.h"
#include "vec2d.h"
#include "intersection.h"

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

class polyServeur : public polygone {
public:
    polyServeur(std::initializer_list<point> &&liste) : polygone(liste) {}

    explicit polyServeur(std::vector<point> points) : polygone(std::move(points)) {}

    pt::ptree to_ptree() {
        pt::ptree root;

        pt::ptree  children;
        for(const auto& elm : points){
            pt::ptree child;
            child.put("x",elm.x);
            child.put("y",elm.y);
            children.push_back(std::make_pair("",std::move(child)));
        }
        root.put("type","polygone");
        root.add_child("points",children);
        return root;
    }

    polyServeur() = default;

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
