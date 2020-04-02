//
// Created by stevlulz on 24/03/2020.
//

#ifndef ASTEROID_CLIENT_H
#define ASTEROID_CLIENT_H

#include <iostream>
#include <thread>
#include "graphiqueSDL.h"

#include "affichableClient.h"

class client{
public:
    //shared objects here
    inline static void client_gui(){
        //main thread for displaying gui

        graphiqueSDL fenetre{1000, 800};
        //pologoneSer a1 = {{100,100}, {200, 200},{300,300},{400,400}};
        //std::cout<< a1.to_string()<<std::endl;

        //pologoneSer r = pologoneSer::json_to_polygoneAC(a1.to_string());
        //std::cout<< r.to_string()<<std::endl;

        //std::cout<<a1.m_center.x<<" "<<a1.m_center.y<<std::endl;
        // exit(1);
        //affichableClient a2 = {{400,400}, {600, 600}};

        affichableClient b1 = {{200,100}, {400, 300},{500,500}};
        //affichableClient b2 = {{500,400}, {700, 600}};

        SDL_Color color = {255, 255,255,  255 };

        b1.DrawFilledPolygon(color,fenetre.renderer);

        SDL_RenderPresent(fenetre.renderer);

        getchar();

        SDL_DestroyRenderer(fenetre.renderer);
        SDL_Quit();
    }

    inline static void client_network_interface(){






    }


    inline static void start(int argc,char**argv){
        argc++;
        argv--;
        std::thread gui(client::client_gui);
        std::thread cni(client::client_network_interface);

        gui.join();
        cni.join();
    }
};


#endif //ASTEROID_CLIENT_H
