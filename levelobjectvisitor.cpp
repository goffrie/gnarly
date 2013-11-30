#include "levelobjectvisitor.h"

#include "levelobject.h"
#include "character.h"
#include "player.h"
#include "itemadapter.h"
#include "monster.h"
#include "gold.h"
#include "staircase.h"

void LevelObjectVisitor::visit(class Character& o) {
    visit(static_cast<LevelObject&>(o));
}
void LevelObjectVisitor::visit(class Player& o) {
    visit(static_cast<Character&>(o));
}
void LevelObjectVisitor::visit(class Monster& o) {
    visit(static_cast<Character&>(o));
}
void LevelObjectVisitor::visit(class ItemAdapter& o) {
    visit(static_cast<LevelObject&>(o));
}
void LevelObjectVisitor::visit(class Gold& o) {
    visit(static_cast<LevelObject&>(o));
}
void LevelObjectVisitor::visit(class Staircase& o) {
    visit(static_cast<LevelObject&>(o));
}
