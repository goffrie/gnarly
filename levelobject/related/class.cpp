#include "class.h"
#include "surface.h"
#include <sstream>
#include "ui.h"
#include "classbuff.h"
#include "player.h"

Class::~Class() {
    for (unsigned int i = 0; i < skills.size(); i++) {
        delete skills[i];
    }
}

bool Class::useSkill(unsigned int i, Player* p) {
    if (i >= skills.size()) {
        return false;
    }
    if (skills[i]->mpCost() > p->currentMP()) {
        UI::instance()->say("Insufficient mana.");
        return false;
    }
    return skills[i]->use(p);
}

void Class::notifyAttack(Player* p) {
    for (unsigned int i = 0; i < skills.size(); i++) {
        skills[i]->notifyAttack(p);
    }
}

void Class::notifyMove(Player* p) {
    for (unsigned int i = 0; i < skills.size(); i++) {
        skills[i]->notifyMove(p);
    }
}

void Class::step(Player* p) {
    for (unsigned int i = 0; i < skills.size(); i++) {
        skills[i]->step(p);
    }
}

std::vector<Skill*> Class::getSkills() {
    return skills;
}

AttributeProvider* Class::getClassBuff(AttributeProvider* a) const {
    return new ClassBuff(a);
}

AttributeProvider* Class::getLevelBuff(AttributeProvider* a) const {
    return new ClassBuff(a);
}

void Class::draw(Surface& target) const {
    for (unsigned int i = 0; i < skills.size(); i++) {
        std::ostringstream line;
        line << "(" << skills[i]->mpCost() << "MP) " << skills[i]->name() << " <" << (char)Skill::getHotkey(i) << ">" << skills[i]->display();
        target.draw(26 + i, 30, line.str());
    }
}
