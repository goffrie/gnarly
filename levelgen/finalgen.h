#ifndef __FINALGEN_H__
#define __FINALGEN_H__

#include "constantgen.h"

// Generation for the final level. There is a fixed layout, and monster spawning is truly random
class FinalGen : public ConstantGen {
    enum { numSpaces = 479 };
protected:
    // Generates the final level with many more monsters than other levels, and monsters 
    // from every level
    virtual Level* genLevel(Player* player, int dungeonLevel); // returns a new'd Level
    virtual int amtEnemies() const { return 70; }
public:
    FinalGen();
};

#endif
