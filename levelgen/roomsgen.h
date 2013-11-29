#ifndef __ROOMS_GEN_H__
#define __ROOMS_GEN_H__

#include "levelgen.h"

class RoomsGen : public LevelGen {
    bool outdoor;
public:
    RoomsGen(int h, int w, bool outdoor = false) : LevelGen(h, w), outdoor(outdoor) { }
protected:
    virtual Dungeon gen() override;
};

#endif
