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

    petitAsteroid(const point& p) {
        points.reserve(5);
        points.emplace_back(p.x - 7, p.y);
        points.emplace_back(p.x, p.y + 7);
        points.emplace_back(p.x + 7, p.y);
        points.emplace_back(p.x + 3, p.y - 7);
        points.emplace_back(p.x - 3, p.y - 7);
    }

    std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {
        return {}; // pas de generation d'asteroid pour les petits asteroids!
    }
};


#endif //ASTEROID_PETITASTEROID_H
