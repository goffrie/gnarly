#ifndef __FILE_GEN_H__
#define __FILE_GEN_H__

#include "levelgen.h"
#include <vector>
#include <string>

class FileGen : public LevelGen {
    std::vector<std::string> layout;
public:
    explicit FileGen(const std::vector<std::string>& layout);

    virtual Dungeon gen() override;
    virtual Level* genLevel(Player* player, int dungeonLevel) override;
};

#endif
