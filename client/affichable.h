//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_AFFICHABLE_H
#define ASTEROID_AFFICHABLE_H

class graphiqueSDL;

class affichable
{
public:
    virtual void afficherSurFenetre(graphiqueSDL& fenetre) const = 0;
};

#endif //ASTEROID_AFFICHABLE_H
