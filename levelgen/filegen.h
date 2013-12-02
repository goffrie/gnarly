#ifndef __FILE_GEN_H__
#define __FILE_GEN_H__

#include "levelgen.h"
#include <vector>
#include <string>

// Generates a level from a fixed layout read from a file
class FileGen : public LevelGen {
    std::vector<std::string> layout;

protected:
    // Places rooms and objects where the layout says to place them
    virtual Dungeon gen();
    virtual Level* genLevel(Player* player, int dungeonLevel);

public:
    explicit FileGen(const std::vector<std::string>& layout);
};

#endif
