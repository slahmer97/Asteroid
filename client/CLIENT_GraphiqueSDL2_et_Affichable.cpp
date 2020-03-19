#include <SDL.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// *****************************************************

struct point
{
    float x, y;
};

struct ligne
{
    point a, b;
};

// *****************************************************

class graphiqueSDL
{
public:
    graphiqueSDL(int largeur, int hauteur);
    ~graphiqueSDL();
    void afficherImage();
    void dessinerLigne(const ligne& l);
    bool isFonctionne() const;
private:
    SDL_Renderer* renderer;
};

graphiqueSDL::graphiqueSDL(int largeur, int hauteur) : renderer{nullptr}
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return;
    SDL_Window* fenetre = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            largeur, hauteur, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

graphiqueSDL::~graphiqueSDL()
{
    SDL_Quit();
}

void graphiqueSDL::afficherImage()
{
    SDL_Event evt;
    SDL_PollEvent(&evt);
    SDL_RenderPresent(renderer);
}

void graphiqueSDL::dessinerLigne(const ligne& l)
{
    SDL_RenderDrawLine(renderer, l.a.x, l.a.y, l.b.x, l.b.y);
}

bool graphiqueSDL::isFonctionne() const
{
    return renderer != nullptr;
}

// *****************************************************

class affichable
{
public:
    affichable(std::initializer_list<ligne> liste);
    void afficherSurFenetre(graphiqueSDL& graphe) const;
private:
    std::vector<ligne> lignes;
};

affichable::affichable(std::initializer_list<ligne> liste) : lignes{liste}
{}

void affichable::afficherSurFenetre(graphiqueSDL& fenetre) const
{
    for (const auto& i : lignes)
        fenetre.dessinerLigne(i);
}

// *****************************************************

int main(int argc, char** argv)
{
    graphiqueSDL fenetre{1000, 800};
    affichable a1 = {{{100,100}, {300, 300}}};
    affichable a2 = {{{400,400}, {600, 600}}};

    affichable b1 = {{{200,100}, {400, 300}}};
    affichable b2 = {{{500,400}, {700, 600}}};

    a1.afficherSurFenetre(fenetre);
    a2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    b1.afficherSurFenetre(fenetre);
    b2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	return 0;
}
