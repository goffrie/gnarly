#ifndef __LEVEL_GEN_H__
#define __LEVEL_GEN_H__

class Dungeon;
class Level;
class Player;

// An abstract class representing a level generation method
class LevelGen {
protected:
    // The height and width of the level to generate
    int height, width;

    // Generates the dungeon
    // May throw GenerationError; in this case, reroll the dungeon.
    virtual Dungeon gen() = 0;
    // Generates the level, placing monsters, items, potions, staircase, and player
    virtual Level* genLevel(Player* player, int dungeonLevel); // returns a new'd Level

    // The amount of gold, potions, and enemies on the level
    virtual int amtGold() const { return 10; }
    virtual int amtPotions() const { return 10; }
    virtual int amtEnemies() const { return 20; }
public:
    class GenerationError {};

    LevelGen(int h, int w) : height(h), width(w) { }
    virtual ~LevelGen() { }

    // Generate a whole level, allocated on the heap.
    Level* generateLevel(Player* player, int dungeonLevel);
};

#endif
