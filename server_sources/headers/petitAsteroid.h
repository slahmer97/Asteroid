//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_PETITASTEROID_H
#define ASTEROID_PETITASTEROID_H

#include "asteroid.h"

class petitAsteroid : public asteroid {
public:
    petitAsteroid(std::initializer_list<point> &&liste) : asteroid(liste) {}

    explicit petitAsteroid(std::vector<point> points) : asteroid(std::move(points)) {}

    std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {
        return {}; // pas de generation d'asteroid pour les petits asteroids!
    }
};


#endif //ASTEROID_PETITASTEROID_H
