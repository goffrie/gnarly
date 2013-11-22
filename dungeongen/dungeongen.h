#ifndef __DUNGEON_GEN_H__
#define __DUNGEON_GEN_H__

class Dungeon;
class DungeonGen {
public:
    virtual Dungeon gen(int height, int width) = 0;
};

#endif
