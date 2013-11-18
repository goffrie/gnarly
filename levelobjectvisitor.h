#ifndef __LEVEL_OBJECT_VISITOR_H__
#define __LEVEL_OBJECT_VISITOR_H__

// A visitor for LevelItems.
// All the methods are default-empty for convenience.
class LevelObjectVisitor {
public:
    virtual void visit(class LevelObject&) {}
    virtual void visit(class Character&) {}
    virtual void visit(class Player&) {}
    virtual void visit(class Monster&) {}
};

#endif
