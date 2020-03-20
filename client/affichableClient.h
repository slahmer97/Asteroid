
#ifndef AFFICHABLE_CLIENT_H
#define AFFICHABLE_CLIENT_H

#include <vector>
#include <initializer_list>
#include "graphiqueSDL.h"

class affichableClient
{
public:
    virtual void afficherSurFenetre(graphiqueSDL& fenetre) const = 0;
};


class polygoneAC: public affichableClient
{
public:
    polygoneAC(std::initializer_list<point> liste) : points{liste}
    {}

    polygoneAC(const std::vector<point>& p) : points{p}
    {}

    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        for (int i = 0; i < points.size() - 1; ++i)
            fenetre.dessinerLigne(points[i], points[i + 1]);
    }
private:
    std::vector<point> points;
};


class alphaNumAC: public affichableClient // ???
{
public:
    // ??? CONSTRUCTEURS
    
    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        // ???
    }
private:
    // ???
    // ???
    // ???
};

#endif //AFFICHABLE_CLIENT_H
