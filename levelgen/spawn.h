#ifndef __SPAWN_H__
#define __SPAWN_H__

class Monster;
class Potion;
class Gold;
class LevelObject;

// An abstract class representing a method of spawning monsters in a level
class Spawn {
public:
    virtual ~Spawn() { }
    // Returns an appropriate random monster
    virtual Monster* randomMonster() = 0;
    // Returns an appropriate random potion
    virtual Potion* randomPotion() = 0;
    // Returns an appropriate random gold pile
    virtual Gold* randomGold() = 0;
    // Gets the corresponding level object to a tile
    virtual LevelObject* getFromTile(char t) { return 0; }
};

#endif
