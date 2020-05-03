
#ifndef ASTEROID_POLYCLIENT_H
#define ASTEROID_POLYCLIENT_H

#include "graphiqueSDL.h"
#include "polygone.h"
#include "affichable.h"

class polyClient : public polygone, public affichable {
public:
    polyClient(std::initializer_list<vec2d> &&liste) : polygone(liste) {}

    explicit polyClient(std::vector<vec2d> points) : polygone(std::move(points)) {}

    explicit polyClient(std::vector<vec2d> &&points) : polygone(points) {}

    void afficherSurFenetre(graphiqueSDL &fenetre) const override {
        fenetre.dessinerPoly({255, 255, 255, 255}, m_center(), points);
    }
};

#endif //ASTEROID_POLYCLIENT_H
