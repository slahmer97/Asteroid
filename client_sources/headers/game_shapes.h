//
// Created by stevlulz on 25/04/2020.
//

#ifndef ASTEROID_GAME_SHAPES_H
#define ASTEROID_GAME_SHAPES_H

#include <memory>
#include <vector>
#include "affichable.h"

class game_shapes{
public:
    static inline std::vector<std::shared_ptr<affichable>> *get_shapes(){
        return &game_shapes::shapes;
    }

    static inline void emplace(std::vector<std::shared_ptr<affichable>>&& new_shapes){
        game_shapes::shapes =  new_shapes;
    }
private:
    static std::vector<std::shared_ptr<affichable>> shapes;
};
#endif //ASTEROID_GAME_SHAPES_H
std::vector<std::shared_ptr<affichable>> game_shapes::shapes{};
