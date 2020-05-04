
#ifndef ASTEROID_ALPHANUMCLIENT_H
#define ASTEROID_ALPHANUMCLIENT_H

#include <string>
#include <utility>
#include "affichable.h"
#include "graphiqueSDL.h"
#include "point.h"

class alphaNumClient : public affichable {
public:

    alphaNumClient() : pos{10, 10} {};

    void afficherSurFenetre(graphiqueSDL &fenetre) const override {
        fenetre.dessinerTexte(val, pos());
    }

    void changeTexte(const std::string &tireX, const std::string &tireV, const std::string &scoreEquipe1,
                     const std::string &scoreEquipe2) {
        val = "SCORE EQUIPE 1: " + scoreEquipe1;
        val += "    SCORE EQUIPE 2 : " + scoreEquipe2;
        val += "    TIRE C: " + tireX;
        val += "    TIRE V: " + tireV;
    }

    void texteDeFin(const std::string &mode, const std::string &won, const std::string &scoreE1, const std::string &scoreE2) {
        pos = {LARGEUR / 2 - 300, HAUTEUR / 2};
        if (mode == "coop") {
            val = "SCORE EQUIPE : " + scoreE1;
        }
        else {
            if (won == "true") val = "GAGNE !";
            else val = "PERDU !";
            val += "SCORE DE L'EQUIPE (1) : " + scoreE1;
            val += "       SCORE DE L'EQUIPE (2) : " + scoreE2;
        }
    }

private:
    std::string val;
    vec2d pos;
};

#endif //ASTEROID_ALPHANUMCLIENT_H
