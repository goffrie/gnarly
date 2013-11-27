#include "levelgen.h"

#include "dungeon.h"
#include "level.h"
#include "staircase.h"
#include "basicspawn.h"
#include "potion.h"
#include "gold.h"
#include "dragongold.h"
#include "monster.h"

#include <vector>

using namespace std;

// A helper class to prevent spinning too many times
// on an impossible task.
struct Gate {
    int max;
    Gate(int max = 10000) : max(max) { }

    void operator()() {
        if (--max <= 0) {
            // We tried too many times. Give up.
            throw LevelGen::GenerationError();
        }
    }
};

Level* LevelGen::generateLevel(Player* player) {
    Gate gate(100);
    while (1) {
        try {
            return genLevel(player);
        } catch (GenerationError&) {
            // retry
        }
        gate();
    }
}

Level* LevelGen::genLevel(Player* player) {
    Level* lvl = new Level(gen());

    const Dungeon& dungeon = lvl->getDungeon();
    BasicSpawn b;
    Gate gate;

    // Place the player.
    pair<int, int> nextPos = dungeon.randomPlacement();
    player->setPos(nextPos.first, nextPos.second);
    lvl->add(player, false);

    // TODO: Handle occupied locations more gracefully.
    {
        // Place/Generate a staircase
        Staircase* stairs = new Staircase;
        while (1) {
            gate();
            nextPos = dungeon.randomPlacement();
            // Find a free position.
            if (!lvl->free(nextPos.first, nextPos.second)) continue;
            // We can't spawn the stairs in the same room as the player...
            // unless there is only one room.
            if (dungeon.numRooms() > 1 &&
                dungeon.inSameRoom(nextPos.first, nextPos.second, player->getY(), player->getX())) continue;

            break;
        }
        stairs->setPos(nextPos.first, nextPos.second);
        lvl->add(stairs);
    }

    // Generate potions.
    const int numberPotions = amtPotions();
    for (int i = 0; i < numberPotions; ++i) {
        do {
            gate();
            nextPos = dungeon.randomPlacement();
        } while (!lvl->free(nextPos.first, nextPos.second));
        Potion* pot = b.randomPotion();
        pot->setPos(nextPos.first, nextPos.second);
        lvl->add(pot);
    }

    int numberDragons = 0;
    // Generate gold.
    const int numberGold = amtGold();
    for (int i = 0; i < numberGold; i++) {
        do {
            do {
                gate();
                nextPos = dungeon.randomPlacement();
            } while (!lvl->free(nextPos.first, nextPos.second));
            Gold* gold = b.randomGold();
            gold->setPos(nextPos.first, nextPos.second);
            lvl->add(gold);

            // If it was a dragon horde, add a dragon, if possible.
            DragonGold* dgold = dynamic_cast<DragonGold*>(gold);
            if (dgold) {
                if (!dgold->addDragon()) {
                    continue;
                }
                numberDragons++;
            }
        } while (false);
    }

    // Generate monsters.
    const int numberEnemies = amtGold() - numberDragons;
    for (int i = 0; i < numberEnemies; ++i) {
        Monster* newEnemy = b.randomMonster();
        do {
            gate();
            nextPos = dungeon.randomPlacement();
        } while (!lvl->free(nextPos.first, nextPos.second));
        newEnemy->setPos(nextPos.first, nextPos.second);
        lvl->add(newEnemy);
    }
    //assert(objects.size() == (unsigned)(numberEnemies + numberGold + numberPotions + 1));

    return lvl;
}
