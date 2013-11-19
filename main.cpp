#include "game.h"
#include <cstdlib>

int main() {
    srand(time(0));
    Game* g = Game::instance();
    g->run();
}
