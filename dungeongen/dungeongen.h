#ifndef __DUNGEON_GEN_H__
#define __DUNGEON_GEN_H__

class Dungeon;
class DungeonGen {
protected:
    // May throw GenerationError; in this case, reroll the dungeon.
    virtual Dungeon gen(int height, int width) = 0;
public:
    class GenerationError {};

    Dungeon generate(int height, int width);
};

#endif
