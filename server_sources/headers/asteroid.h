//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_ASTEROID_H
#define ASTEROID_ASTEROID_H

#include <memory>
#include <random>
#include "polyServeur.h"

class asteroid : public polyServeur {
public:
    asteroid(std::initializer_list<vec2d> &&liste) : polyServeur(liste) {}

    explicit asteroid(std::vector<vec2d> points) : polyServeur(std::move(points)) {}
    asteroid() = default;

    //genere nouveaux asteroids plus petits
    virtual std::vector<vec2d> generationDestruction() const = 0;

    static vec2d directionAlea() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.0, 100.0);
        vec2d d {dist(gen), dist(gen)};
        d.normalize();
        return d;
    }

    static vec2d pointAlea() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist_y(30, HAUTEUR / 3);
        std::uniform_real_distribution<> dist_x(30, LARGEUR - 30);
        return {dist_x(gen), dist_y(gen)};
    }
};

#endif //ASTEROID_ASTEROID_H
