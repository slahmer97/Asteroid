//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_MOYENASTEROID_H
#define ASTEROID_MOYENASTEROID_H

#include "asteroid.h"
#include "petitAsteroid.h"

class moyenAsteroid : public asteroid {
public:
    moyenAsteroid(std::initializer_list<vec2d> &&liste) : asteroid(liste) {}

    explicit moyenAsteroid(std::vector<vec2d> points) : asteroid(std::move(points)) {}

    moyenAsteroid(const vec2d& p, const vec2d& d) {
        direction = d;
        points.reserve(5);
        points.emplace_back(p.x - 15, p.y);
        points.emplace_back(p.x, p.y + 15);
        points.emplace_back(p.x + 10, p.y);
        points.emplace_back(p.x + 5, p.y - 15);
        points.emplace_back(p.x - 5, p.y - 15);
    }

    explicit moyenAsteroid(const vec2d& p) : moyenAsteroid(p, directionAlea()) {}

    [[nodiscard]] std::vector<vec2d> generationDestruction() const override {
        std::vector<vec2d> V = {points[0], points[1]};
        return V;
    }
};

#endif //ASTEROID_MOYENASTEROID_H
