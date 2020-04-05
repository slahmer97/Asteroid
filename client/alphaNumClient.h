//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_ALPHANUMCLIENT_H
#define ASTEROID_ALPHANUMCLIENT_H

#include <string>
#include "affichable.h"
#include "graphiqueSDL.h"
#include "point.h"

class alphaNumClient: public affichable
{
public:
    alphaNumClient(const std::string& val, const point& pos, int taille = 14) : val{val}, pos{pos}, taille{taille} {}
    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        fenetre.dessinerTexte(val, pos, taille);
    }
private:
    std::string val;
    point pos;
    int taille;
};

#endif //ASTEROID_ALPHANUMCLIENT_H
