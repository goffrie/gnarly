#include "game.h"
#include "commandargs.h"
#include <iostream>

int main(int argc, char *argv[]) {
    processArgs(argc, argv);
    Game* g = 0;
    do {
        g = Game::instance(true);
        g->run();
    } while(g->shouldRestart());
}
