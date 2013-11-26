#include "level.h"

#include "dungeon.h"
#include "levelobject.h"
#include "staircase.h"
#include "dragongold.h"
#include "dragon.h"
#include "dungeongen/aggregationgen.h"
#include "dungeongen/bspgen.h"
#include "ui.h"
#include "memory.h"
#include "commandargs.h"
#include "basicspawn.h"
#include "potion.h"
#include "util.h"

#include "shadowcasting/shadowcast.h"

#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

int Level::currentLevel = 0;

Level::Level()
: dungeon(Dungeon::defaultDungeon()),
  grid(dungeon.height(), vector<LevelObject*>(dungeon.width(), 0)),
  fov(dungeon.height(), vector<bool>(dungeon.width(), true)),
  numberGold(10),
  numberPotions(10),
  numberEnemies(20) {
    currentLevel++;
}

Level::~Level() {
    while(!objects.empty()) {
        delete *(objects.begin());
    }
}

void Level::loadLayout(Player* p) {
    vector<string> grid;
    BasicSpawn b;
    for (unsigned int y = 0; y < levelLayout.size(); y++) {
        for (unsigned int x = 0; x < levelLayout[y].size(); x++) {
            if (levelLayout[y][x] == '@') {
                p->setPos(y,x);
                add(p,false);
                continue;
            }
            LevelObject* l = b.getFromTile(levelLayout[y][x]);
            if (l) {
                l->setPos(y, x);
                add(l);
            }
        }
    }
    // XXX fix this maybe
    for (unsigned int y = 0; y < levelLayout.size(); y++) {
        for (unsigned int x = 0; x < levelLayout[y].size(); x++) {
            if (levelLayout[y][x] == 'D') {
                bool placed = false;
                for (int dy = -1; dy <= 1 && !placed; dy++) {
                    for (int dx = -1; dx <= 1 && !placed; dx ++) {
                        if (dy == 0 && dx == 0) {
                            continue;
                        }
                        if (levelLayout[y + dy][x + dx] == '9') {
                            DragonGold* dgold = dynamic_cast<DragonGold*>(objectAt(y + dy, x + dx));
                            if (dgold) {
                                Dragon* d = new Dragon(dgold);
                                d->setPos(y, x);
                                add(d);
                                placed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Level::generate(Player* p) {
    if (!layoutFile.empty()) {
        return loadLayout(p);
    }
    BasicSpawn b;
    // Place the player.
    pair<int, int> nextPos = dungeon.randomPlacement();
    p->setPos(nextPos.first, nextPos.second);
    add(p, false);

    // TODO: Handle occupied locations more gracefully.
    // Place/Generate a staircase
    Staircase* s = new Staircase;
    do {
        nextPos = dungeon.randomPlacement();
    } while (
        !free(nextPos.first, nextPos.second)
        || (dungeon.numRooms() > 1 && dungeon.inSameRoom(nextPos.first, nextPos.second, p->getY(), p->getX()))
    );
    s->setPos(nextPos.first, nextPos.second);
    add(s);

    // Generate potions.
    for (int i = 0; i < numberPotions; ++i) {
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        Potion* pot = b.randomPotion();
        pot->setPos(nextPos.first, nextPos.second);
        add(pot);
    }

    int numberDragons = 0;
    // Generate gold.
    for (int i = 0; i < numberGold; i++) {
        do {
            do {
                nextPos = dungeon.randomPlacement();
            } while (!free(nextPos.first, nextPos.second));
            Gold* gold = b.randomGold();
            gold->setPos(nextPos.first, nextPos.second);
            add(gold);
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
    for (int i = numberDragons; i < numberEnemies; ++i) {
        Monster* newEnemy = b.randomMonster();
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        newEnemy->setPos(nextPos.first, nextPos.second);
        add(newEnemy);
    }
    assert(objects.size() == (unsigned)(numberEnemies + numberGold + numberPotions + 1));
}

void Level::add(LevelObject* i, bool own) {
    assert(!i->level);
    assert(i->y >= 0 && (unsigned) i->y < height());
    assert(i->x >= 0 && (unsigned) i->x < width());
    assert(!grid[i->y][i->x]);

    i->level = this;
    grid[i->y][i->x] = i;
    if (own) {
        objects.insert(i);
    }
}

void Level::remove(LevelObject* l) {
    if (grid[l->y][l->x] == l) {
        grid[l->y][l->x] = 0;
    }
    l->level = 0;
    set<LevelObject*>::iterator it = objects.find(l);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void Level::move(LevelObject* i, int y, int x) {
    // Sanity checks.
    assert(grid[y][x] == 0 || grid[y][x] == i);
    assert(grid[i->y][i->x] == i);

    // Update the grid.
    grid[i->y][i->x] = 0;
    grid[y][x] = i;

    // Update the item.
    i->y = y;
    i->x = x;
}

void Level::notifyDeath(Character* i) {
    dying.push_back(i);
}

void Level::notifyAdd(LevelObject* i) {
    adding.push_back(i);
}

void Level::removeDead() {
    for (unsigned int i = 0; i < dying.size(); i++) {
        UI::instance()->say(capitalize(dying[i]->name(Definite)) + " died.");
        delete dying[i];
    }
    dying.clear();
}

void Level::addStored() {
    for (unsigned int i = 0; i < adding.size(); i++) {
        add(adding[i]);
    }
    adding.clear();
}

bool Level::valid(int y, int x) const {
    return !(x < 0 || y < 0 || (unsigned)x >= width() || (unsigned)y >= height());
}

bool Level::free(int y, int x, bool canGoBetweenRooms) const {
    Tile t = dungeon.tileAt(y, x);
    if (!canGoBetweenRooms) {
        return !grid[y][x] && (t == Floor);
    }
    return !grid[y][x] && (t == Floor || t == Door || t == Passage);
}

void Level::computeFOV(int pY, int pX, int radius) {
    const int h = height(), w = width();
    // Determine which tiles are opaque.
    vector<vector<bool> > opaque(h, vector<bool>(w, true));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Tile tile = tileAt(y, x);
            opaque[y][x] = !(tile == Floor || tile == Door || tile == Passage);
        }
    }
    // Now compute the field of view.
    shadowcast(pY, pX, radius, opaque, fov);
}

void Level::draw(Surface& target) const {
    const int h = height(), w = width();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (!fov[y][x]) continue;
            char tile = tileChar(tileAt(y, x));
            target.draw(y, x, tile);

            LevelObject* obj = objectAt(y, x);
            if (obj) obj->draw(target);
        }
    }
}

void Level::stepObjects() {
    vector<LevelObject*> toStep;
    for (unsigned int y = 0; y < grid.size() ; y++) {
        for (unsigned int x = 0; x < grid[y].size(); x++) {
            if (objects.find(grid[y][x]) != objects.end()) {
                toStep.push_back(grid[y][x]);
            }
        }
    }
    for (unsigned int i = 0; i < toStep.size(); i++) {
        if (!toStep[i]->dead()) {
            toStep[i]->step();
        }
    }
    removeDead();
    addStored();
}

vector<LevelObject*> Level::neighbours(int y, int x) {
    vector<LevelObject*> adjacent;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx ++) {
            if (valid(y + dy, x + dx) && (dy != 0 || dx !=0)) {
                LevelObject* o = grid[y + dy][x + dx];
                if (o) adjacent.push_back(o);
            }
        }
    }
    return adjacent;
}
