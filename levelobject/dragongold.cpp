#include "dragongold.h"
#include "dragon.h"
#include "level.h"

#include <cassert>
#include <utility>
#include <sstream>

DragonGold::DragonGold() : Gold(Gold::DragonH), dragonLives(true) {
}

bool DragonGold::addDragon() {
    assert(getLevel());
    std::vector<std::pair<int, int> > locations = getFreeAdjacent();

    if (locations.size() == 0) {
        return false;
    }
    // Pick one at random.
    std::pair<int, int> newLocation = locations[rand() % locations.size()];
    Dragon* dragon = new Dragon(this);
    dragon->setPos(newLocation.first, newLocation.second);
    getLevel()->add(dragon);
    return true;
}

std::string DragonGold::basicName() const {
    std::ostringstream line;
    line << "dragon horde (" << amount() << " gold)";
    return line.str();
}

std::string DragonGold::name(Article a) const {
    // Use the default implementation in LevelObject, not Gold's override.
    return LevelObject::name(a);
}

bool DragonGold::canPickUp() const {
    return !dragonLives;
}

void DragonGold::notifyDragonDied() {
    dragonLives = false;
}
