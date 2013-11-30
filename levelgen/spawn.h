#ifndef __SPAWN_H__
#define __SPAWN_H__

class Monster;
class Potion;
class Gold;
class LevelObject;

class Spawn {
public:
    virtual ~Spawn() { }
    virtual Monster* randomMonster() = 0;
    virtual Potion* randomPotion() = 0;
    virtual Gold* randomGold() = 0;
    virtual LevelObject* getFromTile(char t) { return 0; }
};

#endif
