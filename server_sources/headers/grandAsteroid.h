//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_GRANDASTEROID_H
#define ASTEROID_GRANDASTEROID_H

#include "asteroid.h"
#include "moyenAsteroid.h"

class grandAsteroid : public asteroid {
public:
    grandAsteroid(std::initializer_list<vec2d> &&liste) : asteroid(liste) {}

    explicit grandAsteroid(std::vector<vec2d> points) : asteroid(std::move(points)) {}

    explicit grandAsteroid(const vec2d& p, const vec2d& d) {
        direction = d;
        points.reserve(5);
        points.emplace_back(p.x - 27, p.y);
        points.emplace_back(p.x, p.y + 27);
        points.emplace_back(p.x + 27, p.y);
        points.emplace_back(p.x + 14, p.y - 27);
        points.emplace_back(p.x - 14, p.y - 27);
    }

    grandAsteroid() : grandAsteroid(pointAlea(), directionAlea()) {}

    [[nodiscard]] std::vector<vec2d> generationDestruction() const override {
        std::vector<vec2d> V = {points[0], points[1]};
        return V;
    }
};

#endif //ASTEROID_GRANDASTEROID_H
