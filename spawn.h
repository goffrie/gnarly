#ifndef __SPAWN_H__
#define __SPAWN_H__

class Monster;
class PotionAdapter;
class Gold;
class LevelObject;

class Spawn {
public:
    virtual Monster* randomMonster() = 0;
    virtual PotionAdapter* randomPotion() = 0;
    virtual Gold* randomGold() = 0;
    virtual LevelObject* getFromTile(char t) { return 0; }
};

#endif
