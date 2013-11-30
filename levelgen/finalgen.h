#ifndef __FINALGEN_H__
#define __FINALGEN_H__

#include "constantgen.h"

class FinalGen : public ConstantGen {
    enum { numSpaces = 479 };
protected:
    virtual Level* genLevel(Player* player, int dungeonLevel); // returns a new'd Level
    virtual int amtEnemies() const { return 70; }
public:
    FinalGen();
};

#endif
