
#ifndef GRAPHIQUE_SDL_H
#define GRAPHIQUE_SDL_H

#include <SDL2/SDL.h>
#include <vector>
#include "param.h"
#include <SDL2/SDL_ttf.h>
#include <vec2.h>
#include "affichable.h"


class graphiqueSDL {
public:
    graphiqueSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return;
        SDL_Window *fenetre = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_SetEventFilter(
                [](void *v, SDL_Event *e) -> int { return (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) ? 1 : 0; },
                NULL);
        cpt = 0;
        valRendu = nullptr;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> num_file(1, 30);
        init_key();
        TTF_Init();
        std::string f = "../client_sources/Fonts/DroidSans" + std::to_string(num_file(gen)) + ".ttf";
        police = TTF_OpenFont(f.c_str(), TAILLEF);
    }

    ~graphiqueSDL() {
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void afficherImage() {
        SDL_Event evt;
        SDL_PollEvent(&evt);
        SDL_RenderPresent(renderer);
    }

    void clearImage() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void update_keys() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    key_pressed(event);
                    break;
                case SDL_KEYUP:
                    key_released(event);
                    break;
            }
        }
    }

    void init_key() {
        up = left = right = fire = fireX2 = fireX3 = false;
    }

    std::vector<bool> getTouche() {
        return std::vector<bool>{this->up, this->right, this->left, this->fire, this->fireX2, this->fireX3};
    }

    void key_pressed(const SDL_Event &e) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                up = true;
                break;
            case SDLK_LEFT:
                left = true;
                break;
            case SDLK_RIGHT:
                right = true;
                break;
            case SDLK_SPACE:
                fire = true;
                break;
            case SDLK_c:
                fireX2 = true;
                break;
            case SDLK_v:
                fireX3 = true;
                break;
        }
    }

    void key_released(const SDL_Event &e) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                up = false;
                break;
            case SDLK_LEFT:
                left = false;
                break;
            case SDLK_RIGHT:
                right = false;
                break;
            case SDLK_SPACE:
                fire = false;
                break;
            case SDLK_c:
                fireX2 = false;
                break;
            case SDLK_v:
                fireX3 = false;
                break;
        }
    }

    void dessinerLigne(const vec2d &a, const vec2d &b) {
        SDL_RenderDrawLine(renderer, a().x, a().y, b().x, b().y);
    }

    void dessinerTexte(const std::string &val, const vec2i &pos) {

        if (cpt % 50 == 0) {
            if (valRendu) SDL_DestroyTexture(valRendu);
            SDL_Surface *aux = TTF_RenderText_Solid(police, val.c_str(), {255, 255, 255, 255});
            valRendu = SDL_CreateTextureFromSurface(renderer, aux);
            SDL_FreeSurface(aux);
        }

        SDL_Rect boite2{pos.x, pos.y, static_cast<int>(TAILLEF * val.length() / 2), TAILLEF};
        SDL_Rect boite1{0, 0, static_cast<int>(TAILLEF * val.length() / 2), TAILLEF};
        SDL_RenderCopy(renderer, valRendu, &boite1, &boite2);

        ++cpt;
    }

    void dessinerPoly(const SDL_Color &color, const vec2i &center, const std::vector<vec2d> &points) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        long size = points.size();
        for (int i = 0; i < size; ++i) {
            dessinerLigne(points[i], points[(i + 1) % size]);
        }
    }

    graphiqueSDL& operator<<(const affichable& a) {
        a.afficherSurFenetre(*this);
        return *this;
    }


private:
    SDL_Renderer *renderer;
    bool up, left, right, fire, fireX2, fireX3;
    TTF_Font *police;
    SDL_Texture *valRendu;
    unsigned cpt;
};

#endif //GRAPHIQUE_SDL_H
