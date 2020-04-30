//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_GRANDASTEROID_H
#define ASTEROID_GRANDASTEROID_H

#include "asteroid.h"
#include "moyenAsteroid.h"
#include <random>

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

    explicit grandAsteroid() : grandAsteroid(pointAlea(), directionAlea()) {}

    [[nodiscard]] std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {
        std::vector<std::shared_ptr<asteroid>> V(2);
        V.emplace_back(new moyenAsteroid{points[0]});
        V.emplace_back(new moyenAsteroid{points[1]});
        return V;
    }
};

#endif //ASTEROID_GRANDASTEROID_H
