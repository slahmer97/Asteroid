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
        points.emplace_back(p.x - 16, p.y);
        points.emplace_back(p.x, p.y + 16);
        points.emplace_back(p.x + 16, p.y);
        points.emplace_back(p.x + 8, p.y - 16);
        points.emplace_back(p.x - 8, p.y - 16);
    }

    [[nodiscard]] std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {

        // placeholder code:

        std::vector<std::shared_ptr<asteroid>> V(3);
        V.emplace_back(new moyenAsteroid{{1, 2},
                                         {3, 4}});
        V.emplace_back(new moyenAsteroid{{1, 2},
                                         {3, 4}});
        V.emplace_back(new moyenAsteroid{{1, 2},
                                         {3, 4}});

        return V;
    }
};

#endif //ASTEROID_GRANDASTEROID_H
