#include "game.h"
#include <cstdlib>

int main() {
    srand(time(0));
    Game* g = 0;
    do {
        g = Game::instance(true);
        g->run();
    } while(g->shouldRestart());
}
