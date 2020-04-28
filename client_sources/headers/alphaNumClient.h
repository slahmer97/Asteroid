//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_ALPHANUMCLIENT_H
#define ASTEROID_ALPHANUMCLIENT_H

#include <string>
#include <utility>
#include "affichable.h"
#include "graphiqueSDL.h"
#include "point.h"

class alphaNumClient: public affichable
{
public:
    alphaNumClient(std::string  val, const vec2d& pos, int taille = 18) : val{std::move(val)}, pos{pos}, taille{taille} {}
    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        fenetre.dessinerTexte(val, pos(), taille);
    }
private:
    std::string val;
    vec2d pos;
    int taille;
};

#endif //ASTEROID_ALPHANUMCLIENT_H
