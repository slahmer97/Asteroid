//
// Created by stevlulz on 24/03/2020.
//

#ifndef ASTEROID_CLIENT_H
#define ASTEROID_CLIENT_H

#include <iostream>
#include <thread>
#include "graphiqueSDL.h"

#include "affichableClient.h"

class client {
public:
    //shared objects here
    static void client_gui() {
        //main thread for displaying gui

        graphiqueSDL fenetre{1000, 800};

        polyClient b1 = {{200, 100},
                         {400, 300},
                         {500, 500}};

        b1.afficherSurFenetre(fenetre);
        fenetre.afficherImage();

        getchar();
    }

    static void client_network_interface() {





    }

    static void start(int argc, char **argv) {
        argc++;
        argv++;
        std::thread gui(client::client_gui);
        std::thread cni(client::client_network_interface);

        gui.join();
        cni.join();
    }
};


#endif //ASTEROID_CLIENT_H
