//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_VAISSEAU_H
#define ASTEROID_VAISSEAU_H

#include "polyServeur.h"
#include "vec2d.h"

class vaisseau : public polyServeur {
public:
    vaisseau(std::initializer_list<point> &&liste) : polyServeur(liste) {}
    explicit vaisseau(std::vector<point> points) : polyServeur(std::move(points)) {}

    vaisseau() : polyServeur{} {
        // construire un triangle
    }

    void rotationDroite(int degree) {
        // placeholder
    }

    void rotationGauche(int degree) {
        // placeholder
    }

    void avancer(const vec2d& v) {
        // placeholder
    }
};

#endif //ASTEROID_VAISSEAU_H
