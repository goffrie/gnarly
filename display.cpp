#include "display.h"

#include "displayable.h"

Display::~Display() {
    // Unhook the display from every item.
    for (std::set<std::pair<int, Displayable*> >::iterator p = items.begin();
            p != items.end();
            ++p) {
        p->second->disp = 0;
    }
}

void Display::add(Displayable* item, int z) {
    item->registerDisplay(this, z);
    items.insert(std::make_pair(z, item));
}

void Display::remove(Displayable* item) {
    items.erase(std::make_pair(item->zIndex, item));
    item->disp = 0;
}

void Display::draw(Grid& grid) const {
    for (std::set<std::pair<int, Displayable*> >::const_iterator p = items.begin();
            p != items.end();
            ++p) {
        p->second->draw(grid);
    }
}
