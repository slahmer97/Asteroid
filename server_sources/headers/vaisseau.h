//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_VAISSEAU_H
#define ASTEROID_VAISSEAU_H

#include "polyServeur.h"

class vaisseau : public polyServeur {
public:
    vaisseau(std::initializer_list<point> &&liste) : polyServeur(liste) {}

    explicit vaisseau(std::vector<point> points) : polyServeur(std::move(points)) {}

    void changerDirection(/*const vec2d& v*/) {



        // placeholder
    }
};

#endif //ASTEROID_VAISSEAU_H
