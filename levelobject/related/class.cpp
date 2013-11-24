#include "class.h"
#include "surface.h"
#include <sstream>

Class::~Class() {
    for (unsigned int i = 0; i < skills.size(); i++) {
        delete skills[i];
    }
}

bool Class::useSkill(unsigned int i, Player* p) {
    if (i >= skills.size()) {
        return false;
    }
    skills[i]->use(p);
    return true;
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

void Class::draw(Surface& target) const {
    for (unsigned int i = 0; i < skills.size(); i++) {
        std::ostringstream line;
        line << skills[i]->name() << " <" << (char)Skill::getHotkey(i) << ">" << skills[i]->display();
        target.draw(26 + i, 30, line.str());
    }
}
