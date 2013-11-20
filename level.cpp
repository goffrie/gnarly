#include "level.h"

#include "dungeon.h"
#include "levelobject.h"

#include <cassert>
#include <algorithm>

using namespace std;

Level::Level()
: dungeon(Dungeon::defaultDungeon()),
  grid(dungeon.height(),
  vector<LevelObject*>(dungeon.width(), 0)),
  numberPotions(10),
  numberEnemies(20) {
    
}

Level::~Level() {
    while(!objects.empty()) {
        delete objects[0];
    }
}

void Level::generate(Player* p) {
    // Place the player.
    pair<int, int> nextPos = dungeon.randomPlacement();
    p->y = nextPos.first;
    p->x = nextPos.second;
    add(p, false);

    // TODO: Handle occupied locations more gracefully.
    // TODO: Place the stairs.

    // Generate potions.
    for (int i = 0; i < numberPotions; ++i) {
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        Potion* pot = randomPotion();
        pot->y = nextPos.first;
        pot->x = nextPos.second;
        add(pot);
    }

    // TODO: Generate gold.

    // Generate monsters.
    for (int i = 0; i < numberEnemies; ++i) {
        Monster* newEnemy = randomMonster();
        do {
            nextPos = dungeon.randomPlacement();
        } while (!free(nextPos.first, nextPos.second));
        newEnemy->y = nextPos.first;
        newEnemy->x = nextPos.second;
        add(newEnemy);
    }
}

void Level::addAllToDisplay(Display *d) {
    d->add(&dungeon);
    for (unsigned int i = 0; i < objects.size(); i++) {
        d->add(objects[i], 1);
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
        objects.push_back(i);
    }
}

void Level::remove(LevelObject* l) {
    if (grid[l->y][l->x] == l) {
        grid[l->y][l->x] = 0;
    }
    vector<LevelObject*>::iterator it = find(objects.begin(), objects.end(), l);
    if (it != objects.end()) {
        next = objects.erase(it);
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

bool Level::valid(int y, int x) const {
    return !(x < 0 || y < 0 || (unsigned)x >= width() || (unsigned)y >= height());
}

bool Level::free(int y, int x) const {
    Tile t = dungeon.tileAt(y, x);
    return !grid[y][x] && (t == Floor || t == Passage || t == Door);
}

void Level::stepObjects() {
    // XXX: steps in the wrong order
    // needs to do it in grid order
    for (next = objects.begin(); next != objects.end(); ) {
        (*(next++))->step();
    }
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
