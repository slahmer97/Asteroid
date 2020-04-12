//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_GRANDASTEROID_H
#define ASTEROID_GRANDASTEROID_H

#include "asteroid.h"
#include "moyenAsteroid.h"

class grandAsteroid : public asteroid {
public:
    grandAsteroid(std::initializer_list<point> &&liste) : asteroid(liste) {}

    explicit grandAsteroid(std::vector<point> points) : asteroid(std::move(points)) {}

    std::vector<std::shared_ptr<asteroid>> generationDestruction() const override {

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
