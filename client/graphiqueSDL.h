
#ifndef GRAPHIQUE_SDL_H
#define GRAPHIQUE_SDL_H

#include "affichable.h"

class graphiqueSDL
{
public:
    graphiqueSDL(int largeur, int hauteur)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return;
        SDL_Window* fenetre = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               largeur, hauteur, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    ~graphiqueSDL()
    {
        SDL_Quit();
    }

    void afficherImage()
    {
        SDL_Event evt;
        SDL_PollEvent(&evt);
        SDL_RenderPresent(renderer);
    }

    void dessinerLigne(const ligne& l)
    {
        SDL_RenderDrawLine(renderer, l.a.x, l.a.y, l.b.x, l.b.y);
    }

    bool isFonctionne() const
    {
        return renderer != nullptr;
    }

private:
    SDL_Renderer* renderer;
};

#endif //GRAPHIQUE_SDL_H
