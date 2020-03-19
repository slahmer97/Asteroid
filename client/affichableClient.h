
#ifndef AFFICHABLE_CLIENT_H
#define AFFICHABLE_CLIENT_H

#include "affichable.h"
#include "graphiqueSDL.h"

class affichableClient : public affichable
{
public:
    using affichable::affichable;
    void afficherSurFenetre(graphiqueSDL& fenetre) const
    {
        for (const auto& i : lignes)
            fenetre.dessinerLigne(i);
    }
};

#endif //AFFICHABLE_CLIENT_H
