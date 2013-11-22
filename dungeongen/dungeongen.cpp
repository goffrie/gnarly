#include "dungeongen.h"

#include "dungeon.h"

Dungeon DungeonGen::generate(int height, int width) {
    while (1) {
        try {
            return gen(height, width);
        } catch (GenerationError&) {
            // retry
        }
    }
}
