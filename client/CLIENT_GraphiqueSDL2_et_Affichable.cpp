
#include <SDL.h>
#include <vector>
#include <chrono>
#include <thread>
#include "graphiqueSDL.h"
#include "affichableClient.h"

// next ---> create affichableServeur class and add JSON in/out to affichableCLIENT&SERVEUR classes

int main(int argc, char** argv)
{
    graphiqueSDL fenetre{1000, 800};
    affichableClient a1 = {{{100,100}, {300, 300}}};
    affichableClient a2 = {{{400,400}, {600, 600}}};

    affichableClient b1 = {{{200,100}, {400, 300}}};
    affichableClient b2 = {{{500,400}, {700, 600}}};

    a1.afficherSurFenetre(fenetre);
    a2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    b1.afficherSurFenetre(fenetre);
    b2.afficherSurFenetre(fenetre);
    fenetre.afficherImage();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	return 0;
}
