
#ifndef GRAPHIQUE_SDL_H
#define GRAPHIQUE_SDL_H

#include <SDL2/SDL.h>
#include <vector>
#include "param.h"
#include <SDL2/SDL_ttf.h>
#include <vec2.h>


class graphiqueSDL {
public:
    graphiqueSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return;
        SDL_Window *fenetre = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_SetEventFilter( [](void* v, SDL_Event* e) -> int {return (e->type == SDL_KEYDOWN) ? 1 : 0;}, NULL);
    }

    ~graphiqueSDL() {
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void afficherImage() {
        SDL_Event evt;
        SDL_PollEvent(&evt);
        SDL_RenderPresent(renderer);
    }
    void clearImage(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    std::string getTouche() {
        std::string s = "";
        SDL_Event e;
        while(s == "") {
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        s = "up";
                        break;
                    case SDLK_DOWN:
                        s = "down";
                        break;
                    case SDLK_LEFT:
                        s = "left";
                        break;
                    case SDLK_RIGHT:
                        s = "right";
                        break;
                    case SDLK_SPACE:
                        s = "space";
                        break;
                }
            }
        }
        if (std::chrono::system_clock::now() - previous_time < std::chrono::milliseconds(50))
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        previous_time = std::chrono::system_clock::now();
        return s;
    }

    void dessinerLigne(const vec2d &a, const vec2d &b) {
        SDL_RenderDrawLine(renderer, a().x, a().y, b().x, b().y);
    }

    void dessinerTexte(const std::string& val, const vec2i& pos, int taille) {
        TTF_Init();
        TTF_Font* police = TTF_OpenFont("../client_sources/DroidSans.ttf", taille);
        SDL_Surface* aux = TTF_RenderText_Solid(police, val.c_str(), {255, 255, 255, 255});
        SDL_Texture* valRendu = SDL_CreateTextureFromSurface(renderer, aux);
        SDL_Rect boite {pos.x, pos.y, static_cast<int>(taille * val.length() / 2), taille};
        SDL_RenderCopy(renderer, valRendu, nullptr, &boite);
        TTF_CloseFont(police);
        SDL_FreeSurface(aux);
        SDL_DestroyTexture(valRendu);
        TTF_Quit();
    }

    void dessinerPolyPlein(const SDL_Color &color, const vec2i &center, const std::vector<vec2d> &points) {

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        long size = points.size();
        for(int i=0;i <size;++i){
           // const_cast<std::vector<vec2d>&>(points)[i].print();
            dessinerLigne(points[i],points[(i+1)%size]);
        }

    }

    bool isFonctionne() const {
        return renderer != nullptr;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> previous_time;
    SDL_Renderer *renderer;
};

#endif //GRAPHIQUE_SDL_H
