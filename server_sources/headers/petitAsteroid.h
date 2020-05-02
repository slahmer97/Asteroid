//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_PETITASTEROID_H
#define ASTEROID_PETITASTEROID_H

#include "asteroid.h"

class petitAsteroid : public asteroid {
public:
    petitAsteroid(std::initializer_list<vec2d> &&liste) : asteroid(liste) {}

    explicit petitAsteroid(std::vector<vec2d> points) : asteroid(std::move(points)) {}

    petitAsteroid(const vec2d& p) {
        points.reserve(5);
        points.emplace_back(p.x - 10, p.y);
        points.emplace_back(p.x, p.y + 7);
        points.emplace_back(p.x + 7, p.y);
        points.emplace_back(p.x + 5, p.y - 7);
        points.emplace_back(p.x - 5, p.y - 10);
    }

    std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {
        return {}; // pas de generation d'asteroid pour les petits asteroids!
    }
};


#endif //ASTEROID_PETITASTEROID_H
