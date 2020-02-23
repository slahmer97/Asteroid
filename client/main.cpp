//
// Created by stevlulz on 23/02/2020.
//


#include <SDL.h>
#include <iostream>
auto main(int argc, char**argv) -> int {

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr<<"could not initialize sdl2: "<< SDL_GetError()<<std::endl;
        return 1;
    }
    window = SDL_CreateWindow(
            "Asteroid hello wolrd",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            500, 500,
            SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        std::cerr<< "could not create window: "<< SDL_GetError()<<std::endl;
        return 1;
    }
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}




