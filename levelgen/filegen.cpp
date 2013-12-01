#include "filegen.h"

#include "dungeon.h"
#include "level.h"
#include "basicspawn.h"
#include "dragongold.h"
#include "dragon.h"

using namespace std;
FileGen::FileGen(const vector<string>& l) : LevelGen(25, 79), layout(l) {
}

Dungeon FileGen::gen() {
    vector<vector<Tile> > d(layout.size());
    for (unsigned int y = 0; y < layout.size(); ++y) {
        d[y].resize(layout[y].size());
        for (unsigned int x = 0; x < layout[y].size(); ++x) {
            d[y][x] = tileFromChar(layout[y][x]);
        }
    }
    return Dungeon(d);
}

Level* FileGen::genLevel(Player* player, int dlvl) {
    Level* lev = new Level(gen());
    BasicSpawn b;
    // Place all players and objects, except dragons
    for (unsigned int y = 0; y < layout.size(); y++) {
        for (unsigned int x = 0; x < layout[y].size(); x++) {
            // Place the player
            if (layout[y][x] == '@') {
                player->setPos(y, x);
                lev->add(player, false);
                continue;
            }
            // Place any other object, other than a dragon
            LevelObject* l = b.getFromTile(layout[y][x]);
            if (l) {
                l->setPos(y, x);
                lev->add(l);
            }
        }
    }
    // Look for dragons
    // XXX fix this maybe
    for (unsigned int y = 0; y < layout.size(); y++) {
        for (unsigned int x = 0; x < layout[y].size(); x++) {
            if (layout[y][x] == 'D') {
                bool placed = false;
                // Try to find a gold that could match with the dragon
                for (int dy = -1; dy <= 1 && !placed; dy++) {
                    for (int dx = -1; dx <= 1 && !placed; dx ++) {
                        if (dy == 0 && dx == 0) {
                            continue;
                        }
                        if (layout[y + dy][x + dx] == '9') {
                            DragonGold* dgold = dynamic_cast<DragonGold*>(lev->objectAt(y + dy, x + dx));
                            if (dgold) {
                                Dragon* d = new Dragon(dgold);
                                d->setPos(y, x);
                                lev->add(d);
                                placed = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return lev;
}
