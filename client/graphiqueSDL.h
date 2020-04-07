
#ifndef GRAPHIQUE_SDL_H
#define GRAPHIQUE_SDL_H

#include <SDL2/SDL.h>
#include <vector>
#include "point.h"
#include <SDL2/SDL_ttf.h>


class graphiqueSDL {
public:
    graphiqueSDL(int largeur, int hauteur) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return;
        SDL_Window *fenetre = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               largeur, hauteur, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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

    void dessinerLigne(const point &a, const point &b) {
        SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
    }

    void dessinerTexte(const std::string& val, const point& pos, int taille) {
        TTF_Init();
        TTF_Font* police = TTF_OpenFont("DroidSans.ttf", taille);
        SDL_Surface* aux = TTF_RenderText_Solid(police, val.c_str(), {255, 255, 255, 255});
        SDL_Texture* valRendu = SDL_CreateTextureFromSurface(renderer, aux);
        SDL_Rect boite {pos.x, pos.y, static_cast<int>(taille * val.length() / 2), taille};
        SDL_RenderCopy(renderer, valRendu, nullptr, &boite);
        TTF_CloseFont(police);
        SDL_FreeSurface(aux);
        SDL_DestroyTexture(valRendu);
        TTF_Quit();
    }

    void dessinerPolyPlein(const SDL_Color &color, const point &center, const std::vector<point> &points) {
        int topY;
        int topCnt;
        int leftCnt;
        int rightCnt;
        int startX;
        int endX;
        int cntY;
        int leftSlope;
        int rightSlope;
        int cnt;
        int numVerts = points.size();
        int numVertsProc = 1;

        topY = points[0].y;
        topCnt = 0;

        for (cnt = 1; cnt < numVerts; cnt++) {
            if (points[cnt].y < topY) {
                topY = points[cnt].y;
                topCnt = cnt;
            }
        }

        leftCnt = topCnt - 1;
        if (leftCnt < 0)
            leftCnt = numVerts - 1;
        rightCnt = topCnt + 1;
        if (rightCnt >= numVerts)
            rightCnt = 0;

        startX = endX = (points[topCnt].x + center.x) << 16;
        cntY = points[topCnt].y;

        if (points[leftCnt].y != points[topCnt].y)
            leftSlope = ((points[leftCnt].x - points[topCnt].x) << 16) / (points[leftCnt].y - points[topCnt].y);
        if (points[rightCnt].y != points[topCnt].y)
            rightSlope = ((points[rightCnt].x - points[topCnt].x) << 16) / (points[rightCnt].y - points[topCnt].y);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        // find slopes
        while (numVertsProc < numVerts) {
            while (cntY < points[leftCnt].y && cntY < points[rightCnt].y) {
                dessinerLigne({startX >> 16, cntY + center.y}, {endX >> 16, cntY + center.y});
                cntY++;
                startX += leftSlope;
                endX += rightSlope;
            }

            if (points[leftCnt].y <= cntY) {
                topCnt = leftCnt;
                leftCnt--;
                if (leftCnt < 0)
                    leftCnt = numVerts - 1;
                if (points[leftCnt].y != points[topCnt].y)
                    leftSlope = ((points[leftCnt].x - points[topCnt].x) << 16) /
                                (points[leftCnt].y - points[topCnt].y);    // find the left side slope

                startX = (points[topCnt].x + center.x) << 16;
                numVertsProc++;
            }

            if (points[rightCnt].y <= cntY) {
                topCnt = rightCnt;
                rightCnt++;
                if (rightCnt == numVerts)
                    rightCnt = 0;
                if (points[rightCnt].y != points[topCnt].y)
                    rightSlope = ((points[rightCnt].x - points[topCnt].x) << 16) /
                                 (points[rightCnt].y - points[topCnt].y); // find the right side slope

                endX = (points[topCnt].x + center.x) << 16;
                numVertsProc++;
            }
            dessinerLigne({startX >> 16, cntY + center.y}, {endX >> 16, cntY + center.y});
        }
    }

    bool isFonctionne() const {
        return renderer != nullptr;
    }

private:
    SDL_Renderer *renderer;
};

#endif //GRAPHIQUE_SDL_H
