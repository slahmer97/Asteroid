
#include <SDL.h>
#include <chrono>
#include <thread>
#include "graphiqueSDL.h"
#include "affichableClient.h"


int main(int argc, char** argv)
{
    graphiqueSDL fenetre{1000, 800};
    polygoneAC a1 = {{100,100}, {300, 300}};
    polygoneAC a2 = {{400,400}, {600, 600}};

    polygoneAC b1 = {{200,100}, {400, 300}};
    polygoneAC b2 = {{500,400}, {700, 600}};

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
