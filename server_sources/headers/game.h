//
// Created by stevlulz on 21/03/2020.
//

#ifndef ASTEROID_GAME_H
#define ASTEROID_GAME_H

#include <iostream>
#include "asteroid.h"
#include "laser.h"
#include "vaisseau.h"

class game {
public:

    explicit game(std::string game_id) : m_game_id{std::move(game_id)}, score{},
                                        asteroids{}, lasers{}, vaisseaux{}
    {}

    void start() {

    }

private:
    std::string m_game_id;
    int score;
    std::vector<std::shared_ptr<asteroid>> asteroids;
    std::vector<std::shared_ptr<laser>> lasers;
    std::map<std::shared_ptr<vaisseau>, int/*idDuJoueur*/> vaisseaux;
    // autre, placeholder
};

#endif //ASTEROID_GAME_H
