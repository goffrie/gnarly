#ifndef __LEVEL_PLAN_H__
#define __LEVEL_PLAN_H__

#include <vector>

class LevelGen;

// A struct representing which level generation methods to use for each floor
struct LevelPlan {
    // The level generation methods to use
    std::vector<LevelGen*> levels;
    LevelPlan() { }
    LevelPlan(const std::vector<LevelGen*>& v) : levels(v) { }

    // The basic method (8 of the same layout with basic generation)
    static const LevelPlan& basicPlan();
    // Gnarly method (4 different randomly generated layouts, and 1 fixed one)
    static const LevelPlan& gnarlyPlan();
};

#endif
