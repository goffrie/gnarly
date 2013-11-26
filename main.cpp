#include "game.h"
#include "commandargs.h"

#include "playerstatus.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    processArgs(argc, argv);
    int seed = time(0);
    srand(seed);
    // XXX Remove this. Used for testing so I can see what produces what
    std::cout << "Random Seed: " << seed << std::endl; 
    try {
        while (true) {
            try {
                // Reset the game and run it.
                Game* g = Game::instance(true);
                g->startGame();
                g->run();
            } catch (RestartGameException&) {
            }
        }
    } catch (QuitGameException&) {
        // User wants to quit, so let them.
    }
}
