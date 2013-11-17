#ifndef __LEVEL_ITEM_VISITOR_H__
#define __LEVEL_ITEM_VISITOR_H__

// A visitor for LevelItems.
// All the methods are default-empty for convenience.
class LevelItemVisitor {
public:
    virtual void visit(class LevelItem&) {}
    virtual void visit(class Character&) {}
    virtual void visit(class Player&) {}
};

#endif
