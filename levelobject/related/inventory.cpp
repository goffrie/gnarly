#include "inventory.h"
#include "item.h"
#include "ui.h"
#include "inventorypopup.h"

using namespace std;

Inventory::Inventory() {
    for (char s = 'z'; s >= 'a'; --s) {
        if (s != 's') slots.push(s);
    }
}

Inventory::~Inventory() {
    for (iterator p = items.begin(); p != items.end(); ++p) {
        delete p->second;
    }
}

bool Inventory::full() const {
    return slots.empty();
}

bool Inventory::useItem(Player& p, char i) {
    iterator it = items.find(i);
    if (it == items.end()) {
        // not found
        return false;
    }
    it->second->use(&p);
    delete it->second;
    items.erase(it);
    slots.push(i);
    return true;
}

char Inventory::addItem(Item* i) {
    if (slots.empty()) return 0;
    char slot = slots.top();
    slots.pop();
    items.insert(make_pair(slot, i));
    return slot;
}

void Inventory::view(Player& p) {
    InventoryPopUp::make(p, *this);
}

Inventory::iterator Inventory::begin() {
    return items.begin();
}

Inventory::const_iterator Inventory::begin() const {
    return items.begin();
}

Inventory::iterator Inventory::end() {
    return items.end();
}

Inventory::const_iterator Inventory::end() const {
    return items.end();
}
