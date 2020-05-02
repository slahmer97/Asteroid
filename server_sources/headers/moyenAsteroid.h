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

    moyenAsteroid(const vec2d& p) {
        points.reserve(5);
        points.emplace_back(p.x - 15, p.y);
        points.emplace_back(p.x, p.y + 15);
        points.emplace_back(p.x + 10, p.y);
        points.emplace_back(p.x + 5, p.y - 15);
        points.emplace_back(p.x - 5, p.y - 15);
    }

    [[nodiscard]] std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {
        std::vector<std::shared_ptr<asteroid>> V(2);
        V.emplace_back(new petitAsteroid{points[0]});
        V.emplace_back(new petitAsteroid{points[1]});
        return V;
    }
};

#endif //ASTEROID_MOYENASTEROID_H
