#include "potion.h"

#include "player.h"
#include "ui.h"

bool Potion::used[6] = {false, false, false, false, false, false};

void Potion::use(Player* target) {
    used[type] = true;
    UI::instance()->say("You drink " + name(Indefinite) + ".");
    switch (type) {
        case RH: target->heal(10); break;
        case PH: target->heal(-10); break;
        case BA: target->applyBuff(5, 0); break;
        case WA: target->applyBuff(-5, 0); break;
        case BD: target->applyBuff(0, 5); break;
        case WD: target->applyBuff(0, -5); break;
    }
}

std::string Potion::basicName() const {
    if (!used[type]) {
        return "unknown potion";
    }
    switch (type) {
        case RH: return "potion of restore health";
        case PH: return "potion of poison health";
        case BA: return "potion of boost attack";
        case WA: return "potion of wound attack";
        case BD: return "potion of boost defense";
        case WD: return "potion of wound defense";
        default: std::terminate();
    }
}

void Potion::resetUsed() {
    for (int i = 0; i < numTypes; i++) {
        used[i] = false;
    }
}
