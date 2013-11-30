#include "finalgen.h"
#include "dungeon.h"
#include "level.h"
#include "gnarlyspawn.h"
#include "monster.h"
#include "rand.h"
#include "altar.h"
#include <vector>
#include <memory>

using namespace std;

static const Dungeon finalDungeon(
    "|-----------------------------------------------------------------------------|\n"
    "|                                                                             |\n"
    "|  |---------|                     #########                     |---------|  |\n"
    "|  |.........|                     #########                     |.........|  |\n"
    "|  |.........|                     #########                     |.........|  |\n"
    "|  |.........|                     #########                     |.........|  |\n"
    "|  |.........|                     #########                     |.........|  |\n"
    "|  |---|...|-|                         #                         |-|...|---|  |\n"
    "|      |...|                           #                           |...|      |\n"
    "|      |...|                           #                           |...|      |\n"
    "|  |---|...|-------------------------| # |-------------------------|...|---|  |\n"
    "|  |.................................| # |.................................|  |\n"
    "|  |.................................| # |.................................|  |\n"
    "|  |...|-+-|......|-+-|......|-+-|...| # |...|-+-|......|-+-|......|-+-|...|  |\n"
    "|  |...|###|......|###|......|###|...|-+-|...|###|......|###|......|###|...|  |\n"
    "|  |...+###+......+###+......+###+...........+###+......+###+......+###+...|  |\n"
    "|  |...|###|......|###|......|###|...|-+-|...|###|......|###|......|###|...|  |\n"
    "|  |...|-+-|......|-+-|......|-+-|...| # |...|-+-|......|-+-|......|-+-|...|  |\n"
    "|  |.................................+###+.................................|  |\n"
    "|  |---------------------------------|   |---------------------------------|  |\n"
    "|                                                                             |\n"
    "|                                                                             |\n"
    "|                                                                             |\n"
    "|                                                                             |\n"
    "|-----------------------------------------------------------------------------|\n"
);

FinalGen::FinalGen() : ConstantGen(finalDungeon) { }



Level* FinalGen::genLevel(Player* player, int dungeonLevel) {
    auto_ptr<Level> lvl(new Level(gen()));
    GnarlySpawn b(dungeonLevel, true);

    // Place the player.
    player->setPos(4, 39);
    lvl->add(player, false);

    Altar* altar1 = new Altar();
    altar1->setPos(3, 7);
    lvl->add(altar1);
    Altar* altar2 = new Altar();
    altar2->setPos(3, 71);
    lvl->add(altar2);

    double numVisited = 0;
    double numEnemies = amtEnemies();
    // Generate monsters.
    for (unsigned int y = 0; y < lvl->height(); y++) {
        for (unsigned int x = 0; x < lvl->width(); x++) {
            if (lvl->free(y, x)) {
                if (rnd.dbl(0,1) < numEnemies / (numSpaces - numVisited)) {
                    Monster* newEnemy = b.randomMonster();
                    newEnemy->setPos(y, x);
                    lvl->add(newEnemy);
                    numEnemies--;
                }
                numVisited++;
            }
        }
    }

    return lvl.release();
}
