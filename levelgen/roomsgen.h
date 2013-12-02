#ifndef __ROOMS_GEN_H__
#define __ROOMS_GEN_H__

#include "levelgen.h"

// Map generation that creates and connexts rooms, either indoors or outdoors.
// Indoor mode is similar to the basic layout
class RoomsGen : public LevelGen {
    // Whether or not it is indoors or outdoors
    bool outdoor;
public:
    RoomsGen(int h, int w, bool outdoor = false) : LevelGen(h, w), outdoor(outdoor) { }
protected:
    // Randomly generates the dungeon
    virtual Dungeon gen();
};

#endif
