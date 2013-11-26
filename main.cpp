#include "game.h"
#include "commandargs.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    processArgs(argc, argv);
    int seed = time(0);
    srand(seed);
    // XXX Remove this. Used for testing so I can see what produces what
    std::cout << "Random Seed: " << seed << std::endl; 
    Game* g = 0;
    do {
        g = Game::instance(true);
        g->run();
    } while(g->shouldRestart());
}
