#ifndef __BSP_GEN_H__
#define __BSP_GEN_H__

#include "dungeongen.h"

class BSPGen : public DungeonGen {
protected:
    virtual Dungeon gen(int height, int width) override;
};

#endif
