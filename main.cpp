#include "game.h"
#include <cstdlib>
#include <iostream>

int main() {
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
