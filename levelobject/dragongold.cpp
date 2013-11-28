#include "dragongold.h"
#include "dragon.h"
#include "level.h"
#include "rand.h"

#include <cassert>
#include <utility>
#include <sstream>

using namespace std;

DragonGold::DragonGold() : Gold(Gold::DragonH), dragonLives(true) {
}

bool DragonGold::addDragon() {
    assert(getLevel());
    vector<pair<int, int> > locations = getFreeAdjacent();

    if (locations.size() == 0) {
        return false;
    }
    // Pick one at random.
    pair<int, int> newLocation = locations[rnd(0, locations.size())];
    Dragon* dragon = new Dragon(this);
    dragon->setPos(newLocation.first, newLocation.second);
    getLevel()->add(dragon);
    return true;
}

string DragonGold::basicName() const {
    ostringstream line;
    line << "dragon horde (" << amount() << " gold)";
    return line.str();
}

string DragonGold::name(Article a) const {
    // Use the default implementation in LevelObject, not Gold's override.
    return LevelObject::name(a);
}

bool DragonGold::canPickUp() const {
    return !dragonLives;
}

void DragonGold::notifyDragonDied() {
    dragonLives = false;
}
