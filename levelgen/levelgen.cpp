#include "levelgen.h"

#include "dungeon.h"
#include "level.h"
#include "staircase.h"
#include "gnarlyspawn.h"
#include "potionadapter.h"
#include "gold.h"
#include "dragongold.h"
#include "monster.h"

#include <vector>
#include <memory>

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

Level* LevelGen::generateLevel(Player* player, int dungeonLevel) {
    Gate gate(100);
    while (1) {
        try {
            return genLevel(player, dungeonLevel);
        } catch (GenerationError&) {
            // retry
        }
        gate();
    }
}

Level* LevelGen::genLevel(Player* player, int dungeonLevel) {
    auto_ptr<Level> lvl(new Level(gen()));

    const Dungeon& dungeon = lvl->getDungeon();
    GnarlySpawn b(dungeonLevel);
    Gate gate;

    // Place the player.
    pair<int, int> nextPos = dungeon.randomPlacement();
    player->setPos(nextPos.first, nextPos.second);
    lvl->add(player, false);

    // TODO: Handle occupied locations more gracefully.
    {
        // Place/Generate a staircase
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
        Staircase* stairs = new Staircase;
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
        PotionAdapter* pot = b.randomPotion();
        pot->setPos(nextPos.first, nextPos.second);
        lvl->add(pot);
    }

    int numberDragons = 0;
    // Generate gold.
    const int numberGold = amtGold();
    for (int i = 0; i < numberGold; i++) {
        do {
            gate();
            nextPos = dungeon.randomPlacement();
        } while (!lvl->free(nextPos.first, nextPos.second));
        Gold* gold = b.randomGold();
        gold->setPos(nextPos.first, nextPos.second);
        lvl->add(gold);

        // If it was a dragon horde, add a dragon, if possible.
        DragonGold* dgold = dynamic_cast<DragonGold*>(gold);
        if (dgold && dgold->addDragon()) {
            numberDragons++;
        }
    }

    // Generate monsters.
    const int numberEnemies = amtEnemies() - numberDragons;
    for (int i = 0; i < numberEnemies; ++i) {
        do {
            gate();
            nextPos = dungeon.randomPlacement();
        } while (!lvl->free(nextPos.first, nextPos.second));
        Monster* newEnemy = b.randomMonster();
        newEnemy->setPos(nextPos.first, nextPos.second);
        lvl->add(newEnemy);
    }

    return lvl.release();
}
