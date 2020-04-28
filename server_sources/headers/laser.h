//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_LASER_H
#define ASTEROID_LASER_H

#include "polyServeur.h"

class laser : public polyServeur {
public:
    laser(std::initializer_list<vec2d> &&liste) : polyServeur(liste) {}

    explicit laser(std::vector<vec2d> points) : polyServeur(std::move(points)) {}
};

#endif //ASTEROID_LASER_H
