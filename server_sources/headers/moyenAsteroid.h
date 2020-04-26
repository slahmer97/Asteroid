//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_MOYENASTEROID_H
#define ASTEROID_MOYENASTEROID_H

#include "asteroid.h"
#include "petitAsteroid.h"

class moyenAsteroid : public asteroid {
public:
    moyenAsteroid(std::initializer_list<point> &&liste) : asteroid(liste) {}

    explicit moyenAsteroid(std::vector<point> points) : asteroid(std::move(points)) {}

    moyenAsteroid(const point& p) {
        points.reserve(5);
        points.emplace_back(p.x - 10, p.y);
        points.emplace_back(p.x, p.y + 10);
        points.emplace_back(p.x + 10, p.y);
        points.emplace_back(p.x + 5, p.y - 10);
        points.emplace_back(p.x - 5, p.y - 10);
    }

    std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {

        // placeholder code:

        std::vector<std::shared_ptr<asteroid>> V(3);
        V.emplace_back(new petitAsteroid{{1, 2},
                                         {3, 4}});
        V.emplace_back(new petitAsteroid{{1, 2},
                                         {3, 4}});
        V.emplace_back(new petitAsteroid{{1, 2},
                                         {3, 4}});

        return V;
    }
};

#endif //ASTEROID_MOYENASTEROID_H
