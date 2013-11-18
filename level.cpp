#include "level.h"

#include "dungeon.h"
#include "levelobject.h"

#include <cassert>

using namespace std;

Level::Level()
: dungeon(Dungeon::defaultDungeon()),
  grid(dungeon.height(),
  vector<LevelObject*>(dungeon.width(), 0)),
  numberEnemies(20) {
    
}

Level::~Level() {
    for (unsigned int i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
}

void Level::generate(Player* p) {
    pair<int,int> nextPos = dungeon.randomPlacement();
    p->moveTo(nextPos.first, nextPos.second);

    for (int i = 0; i < numberEnemies; i++) {
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
    return x < 0 || y < 0 || (unsigned)x >= width() || (unsigned)y >= height();
}

bool Level::free(int y, int x) const {
    Tile t = dungeon.tileAt(y, x);
    return !grid[y][x] && (t == Floor || t == Passage || t == Door);
}

bool Level::movable(int y, int x) const {
    struct IsGoldVisitor : public LevelObjectVisitor {
        bool ans;
        // TODO: when gold is implemented, check for it
        // XXX: also staircases
    };
    IsGoldVisitor v;
    v.ans = false;
    if (grid[y][x]) {
        grid[y][x]->accept(v);
        if (!v.ans) return false;
    }
    Tile t = dungeon.tileAt(y, x);
    return (t == Floor || t == Passage || t == Door);
}

void Level::stepObjects() {
    for (unsigned int i = 0; i < objects.size(); i++) {
        objects[i]->step();
    }
}

vector<LevelObject*> Level::getAdjacent(int y, int x) {
    vector<LevelObject*> adjacent;
    for (unsigned int dy = -1; dy <= 1; dy++) {
        for (unsigned int dx = -1; dx <= 1; dx ++) {
            if (valid(y + dy, x + dx) && (dy != 0 || dx !=0)) {
                adjacent.push_back(grid[y + dy][x + dx]);
            }
        }
    }
    return adjacent;
}
