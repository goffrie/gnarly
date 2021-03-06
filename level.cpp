#include "level.h"

#include "dungeon.h"
#include "levelobject.h"
#include "dragongold.h"
#include "dragon.h"
#include "ui.h"
#include "commandargs.h"
#include "levelgen/basicspawn.h"
#include "util.h"

#include "shadowcasting/shadowcast.h"

#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

struct LevelImpl {
    // The base dungeon layout. Owned by this class.
    Dungeon dungeon;

    // A catalogue of the things on this level,
    // indexed by their location.
    vector<vector<LevelObject*> > grid;

    // What tiles are currently visible by the player?
    // Needs to be kept up-to-date using `computeFOV`.
    vector<vector<bool> > fov;

    // All the items owned by this level.
    // This includes everything except the player.
    set<LevelObject*> objects;
    set<Character*> dying;

    LevelImpl(Dungeon layout) : dungeon(layout),
        grid(dungeon.height(), vector<LevelObject*>(dungeon.width(), 0)),
        fov(dungeon.height(), vector<bool>(dungeon.width(), true)) {
    }
};

Level::Level(Dungeon layout) : d(new LevelImpl(layout)) {
}

Level::~Level() {
    while (!d->objects.empty()) {
        delete *d->objects.begin();
    }
    delete d;
}

// Accessor methods.
unsigned int Level::height() const {
    return d->grid.size();
}
unsigned int Level::width() const {
    return d->grid[0].size();
}

const Dungeon& Level::getDungeon() const {
    return d->dungeon;
}
Tile Level::tileAt(int y, int x) const {
    return d->dungeon.tileAt(y, x);
}
LevelObject* Level::objectAt(int y, int x) const {
    return d->grid[y][x];
}

bool Level::valid(int y, int x) const {
    return !(x < 0 || y < 0 || (unsigned)x >= width() || (unsigned)y >= height());
}

void Level::add(LevelObject* i, bool own) {
    // Sanity checks.
    assert(!i->level);
    assert(i->y >= 0 && (unsigned) i->y < height());
    assert(i->x >= 0 && (unsigned) i->x < width());
    assert(!d->grid[i->y][i->x]);

    // Add this to the object, the object to the grid, and the object to the level
    // if it was requested
    i->level = this;
    d->grid[i->y][i->x] = i;
    if (own) {
        d->objects.insert(i);
    }
}

void Level::remove(LevelObject* l) {
    if (d->grid[l->y][l->x] == l) {
        d->grid[l->y][l->x] = 0;
    }
    l->level = 0;
    d->objects.erase(l);
}

void Level::move(LevelObject* i, int y, int x) {
    // Sanity checks.
    assert(d->grid[y][x] == 0 || d->grid[y][x] == i);
    assert(d->grid[i->y][i->x] == i);

    // Update the grid.
    d->grid[i->y][i->x] = 0;
    d->grid[y][x] = i;

    // Update the item.
    i->y = y;
    i->x = x;
}

void Level::notifyDeath(Character* i) {
    // Queue it up for death
    bool removed = d->dying.insert(i).second;
    if (removed) {
        assert(d->grid[i->y][i->x] == i);
        d->grid[i->y][i->x] = 0;
    }
}

void Level::removeDead() {
    for (set<Character*>::iterator p = d->dying.begin(); p != d->dying.end(); ++p) {
        UI::instance()->say(capitalize((*p)->name(Definite)) + " died.");
        d->objects.erase(*p);
        (*p)->level = 0;
        delete *p;
    }
    d->dying.clear();
}

bool Level::free(int y, int x, bool canGoBetweenRooms) const {
    Tile t = tileAt(y, x);
    if (!canGoBetweenRooms) {
        return !d->grid[y][x] && (t == Floor);
    }
    return !d->grid[y][x] && (t == Floor || t == Door || t == Passage);
}

// Determine which tiles are opaque.
vector<vector<bool> > Level::getOpaque() const {
    const int h = height(), w = width();
    vector<vector<bool> > opaque(h, vector<bool>(w, true));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Tile tile = tileAt(y, x);
            opaque[y][x] = !(tile == Floor || tile == Door || tile == Passage);
        }
    }
    return opaque;
}

// Compute the field of view.
void Level::computeFOV(int pY, int pX, int radius) {
    shadowcast(pY, pX, radius, getOpaque(), d->fov);
}

void Level::draw(Surface& target) const {
    const int h = height(), w = width();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            // Draw things based on what you can see
            if (!d->fov[y][x]) continue;
            drawTile(tileAt(y, x), target, y, x);

            LevelObject* obj = objectAt(y, x);
            if (obj) obj->draw(target);
        }
    }
}

vector<LevelObject*> Level::getVisible(int pY, int pX, int radius) const {
    const int h = height(), w = width();
    // Compute the field of view.
    vector<vector<bool> > field;
    shadowcast(pY, pX, radius, getOpaque(), field);

    vector<LevelObject*> objects;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (field[y][x]) {
                LevelObject* o = objectAt(y, x);
                if (o) objects.push_back(o);
            }
        }
    }
    return objects;
}

void Level::stepObjects() {
    vector<LevelObject*> toStep;
    // Get everything we need to step, sorted by position, and add them
    for (unsigned int y = 0; y < d->grid.size() ; y++) {
        for (unsigned int x = 0; x < d->grid[y].size(); x++) {
            if (d->objects.find(d->grid[y][x]) != d->objects.end()) {
                toStep.push_back(d->grid[y][x]);
            }
        }
    }
    // Step everything
    for (unsigned int i = 0; i < toStep.size(); i++) {
        if (!toStep[i]->dead()) {
            toStep[i]->step();
        }
    }
    // Remove dead stuffs
    removeDead();
}

vector<LevelObject*> Level::neighbours(int y, int x) {
    vector<LevelObject*> adjacent;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx ++) {
            if (valid(y + dy, x + dx) && (dy != 0 || dx !=0)) {
                LevelObject* o = d->grid[y + dy][x + dx];
                if (o) adjacent.push_back(o);
            }
        }
    }
    return adjacent;
}
