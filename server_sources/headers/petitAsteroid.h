
#ifndef ASTEROID_PETITASTEROID_H
#define ASTEROID_PETITASTEROID_H

#include "asteroid.h"

class petitAsteroid : public asteroid {
public:
    petitAsteroid(std::initializer_list<vec2d> &&liste) : asteroid(liste) {}

    explicit petitAsteroid(std::vector<vec2d> points) : asteroid(std::move(points)) {}

    petitAsteroid(const vec2d &p, const vec2d &d) {
        direction = d;
        points.reserve(5);
        points.emplace_back(p.x - 10, p.y);
        points.emplace_back(p.x, p.y + 7);
        points.emplace_back(p.x + 7, p.y);
        points.emplace_back(p.x + 5, p.y - 7);
        points.emplace_back(p.x - 5, p.y - 10);
    }

    explicit petitAsteroid(const vec2d &p) : petitAsteroid(p, directionAlea()) {}

    std::vector<vec2d> generationDestruction() const override {
        return {}; // pas de generation d'asteroid pour les petits asteroids!
    }
};


#endif //ASTEROID_PETITASTEROID_H
