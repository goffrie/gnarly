#include "level.h"

#include "dungeon.h"
#include "levelobject.h"
#include "staircase.h"

#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

Level::Level(Display* d)
: dungeon(Dungeon::defaultDungeon()),
  display(d),
  grid(dungeon.height(), vector<LevelObject*>(dungeon.width(), 0)),
  numberGold(10),
  numberPotions(10),
  numberEnemies(20) {
    display->add(&dungeon);
}

Level::~Level() {
    while(!objects.empty()) {
        delete *(objects.begin());
    }
}

void Level::generate(Player* p) {
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
        && !dungeon.inSameRoom(nextPos.first, nextPos.second, p->getX(), p->getY())
    );
    s->setPos(nextPos.first, nextPos.second);
    add(s);

    // Generate potions.
    for (int i = 0; i < numberPotions; ++i) {
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        Potion* pot = randomPotion();
        pot->setPos(nextPos.first, nextPos.second);
        add(pot);
    }

    // Generate gold.
    for (int i = 0; i < numberGold; i++) {
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        Gold* gold = randomGold();
        gold->setPos(nextPos.first, nextPos.second);
        add(gold);
    }

    // Generate monsters.
    for (int i = 0; i < numberEnemies; ++i) {
        Monster* newEnemy = randomMonster();
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        newEnemy->setPos(nextPos.first, nextPos.second);
        add(newEnemy);
    }
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
        display->add(i, 1);
    }
}

void Level::remove(LevelObject* l) {
    if (grid[l->y][l->x] == l) {
        grid[l->y][l->x] = 0;
    }
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

bool Level::free(int y, int x) const {
    Tile t = dungeon.tileAt(y, x);
    return !grid[y][x] && (t == Floor || t == Passage || t == Door);
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
