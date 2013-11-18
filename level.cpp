#include "level.h"

#include "dungeon.h"
#include "levelobject.h"

#include <cassert>

using namespace std;

Level::Level(Dungeon& dungeon) : dungeon(dungeon),
    grid(dungeon.height(), vector<LevelObject*>(dungeon.width(), 0)) {
}

Level::~Level() {
    for (unsigned int i = 0; i < items.size(); ++i) {
        delete items[i];
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
        items.push_back(i);
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

bool Level::free(int y, int x) const {
    Tile t = dungeon.tileAt(y, x);
    return !grid[y][x] && (t == Floor || t == Passage || t == Door);
}

bool Level::movable(int y, int x) const {
    struct IsGoldVisitor : public LevelObjectVisitor {
        bool ans;
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
