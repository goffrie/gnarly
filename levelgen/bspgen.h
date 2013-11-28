#ifndef __BSP_GEN_H__
#define __BSP_GEN_H__

#include "levelgen.h"

class BSPGen : public LevelGen {
protected:
    virtual Dungeon gen() override;
public:
    BSPGen(int h, int w) : LevelGen(h, w) { }
    virtual int amtEnemies() const { return 30; }
};

#endif
