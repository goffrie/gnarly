#ifndef __DUNGEON_GEN_H__
#define __DUNGEON_GEN_H__

class Dungeon;
class Level;
class Player;
class DungeonGen {
protected:
    int height, width;

    // May throw GenerationError; in this case, reroll the dungeon.
    virtual Dungeon gen() = 0;
    virtual Level* genLevel(Player* player); // returns a new'd Level

    virtual int amtGold() const { return 10; }
    virtual int amtPotions() const { return 10; }
    virtual int amtEnemies() const { return 20; }
public:
    class GenerationError {};

    DungeonGen(int h, int w) : height(h), width(w) { }
    virtual ~DungeonGen() { }

    // Just generate a dungeon.
    // XXX
    Dungeon generateLayout();
    // Generate a whole level, allocated on the heap.
    Level* generateLevel(Player* player);
};

#endif
