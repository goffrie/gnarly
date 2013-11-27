#include "level.h"

#include "dungeon.h"
#include "levelobject.h"
#include "dragongold.h"
#include "dragon.h"
#include "ui.h"
#include "commandargs.h"
#include "basicspawn.h"
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
    std::vector<std::vector<LevelObject*> > grid;

    // What tiles are currently visible by the player?
    // Needs to be kept up-to-date using `computeFOV`.
    std::vector<std::vector<bool> > fov;

    // All the items owned by this level.
    // This includes everything except the player.
    std::set<LevelObject*> objects;
    std::vector<Character*> dying;
    std::vector<LevelObject*> adding;

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

// Load the layout specified on the command line.
// XXX XXX
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

void Level::add(LevelObject* i, bool own) {
    assert(!i->level);
    assert(i->y >= 0 && (unsigned) i->y < height());
    assert(i->x >= 0 && (unsigned) i->x < width());
    assert(!d->grid[i->y][i->x]);

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
    set<LevelObject*>::iterator it = d->objects.find(l);
    if (it != d->objects.end()) {
        d->objects.erase(it);
    }
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
    d->dying.push_back(i);
}

void Level::notifyAdd(LevelObject* i) {
    d->adding.push_back(i);
}

void Level::removeDead() {
    for (unsigned int i = 0; i < d->dying.size(); i++) {
        UI::instance()->say(capitalize(d->dying[i]->name(Definite)) + " died.");
        delete d->dying[i];
    }
    d->dying.clear();
}

void Level::addStored() {
    for (unsigned int i = 0; i < d->adding.size(); i++) {
        add(d->adding[i]);
    }
    d->adding.clear();
}

bool Level::free(int y, int x, bool canGoBetweenRooms) const {
    Tile t = tileAt(y, x);
    if (!canGoBetweenRooms) {
        return !d->grid[y][x] && (t == Floor);
    }
    return !d->grid[y][x] && (t == Floor || t == Door || t == Passage);
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
    shadowcast(pY, pX, radius, opaque, d->fov);
}

void Level::draw(Surface& target) const {
    const int h = height(), w = width();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (!d->fov[y][x]) continue;
            char tile = tileChar(tileAt(y, x));
            target.draw(y, x, tile);

            LevelObject* obj = objectAt(y, x);
            if (obj) obj->draw(target);
        }
    }
}

// XXX dupe code
vector<LevelObject*> Level::getVisible(int pY, int pX, int radius) const {
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
    vector<vector<bool> > field;
    shadowcast(pY, pX, radius, opaque, field);

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
    for (unsigned int y = 0; y < d->grid.size() ; y++) {
        for (unsigned int x = 0; x < d->grid[y].size(); x++) {
            if (d->objects.find(d->grid[y][x]) != d->objects.end()) {
                toStep.push_back(d->grid[y][x]);
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
                LevelObject* o = d->grid[y + dy][x + dx];
                if (o) adjacent.push_back(o);
            }
        }
    }
    return adjacent;
}
