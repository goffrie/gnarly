#ifndef __BSP_GEN_H__
#define __BSP_GEN_H__

#include "dungeongen.h"

class BSPGen : public DungeonGen {
protected:
    virtual Dungeon gen() override;
public:
    BSPGen(int h, int w) : DungeonGen(h, w) { }
};

#endif
