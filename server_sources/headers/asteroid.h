//
// Created by parallels on 4/12/20.
//

#ifndef ASTEROID_ASTEROID_H
#define ASTEROID_ASTEROID_H

#include <memory>
#include "polyServeur.h"

class asteroid : public polyServeur {
public:
    asteroid(std::initializer_list<point> &&liste) : polyServeur(liste) {}

    explicit asteroid(std::vector<point> points) : polyServeur(std::move(points)) {}

    //genere nouveaux asteroids plus petits
    virtual std::vector<std::shared_ptr<asteroid>> generationDestruction() const = 0;
};

#endif //ASTEROID_ASTEROID_H
