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
    static inline std::vector<std::shared_ptr<polyClient>> *get_shapes(){
        return &game_shapes::shapes;
    }
    static inline void init(){
      //  int a=10;
     //   std::cout<<a;
    }

    static inline void emplace(std::vector<std::shared_ptr<polyClient>>&& new_shapes){
        game_shapes::shapes =  new_shapes;
    }
private:
    static std::vector<std::shared_ptr<polyClient>> shapes;

};
#endif //ASTEROID_GAME_SHAPES_H
std::vector<std::shared_ptr<polyClient>> game_shapes::shapes{};
