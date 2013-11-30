#ifndef __LEVEL_OBJECT_VISITOR_H__
#define __LEVEL_OBJECT_VISITOR_H__

// A visitor for LevelObjects.
// All the methods for subclasses are defaulted to "call up" to the
// method for the parent class.

class LevelObject;
class Character;
class Player;
class Monster;
class ItemAdapter;
class Gold;
class Staircase;

class LevelObjectVisitor {
public:
    virtual void visit(LevelObject&) { }
    virtual void visit(Character& o);
    virtual void visit(Player& o);
    virtual void visit(Monster& o);
    virtual void visit(ItemAdapter& o);
    virtual void visit(Gold& o);
    virtual void visit(Staircase& o);
};

#endif
