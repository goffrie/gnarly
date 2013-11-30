#ifndef __LEVEL_PLAN_H__
#define __LEVEL_PLAN_H__

#include <vector>
#include <string>

class LevelGen;

struct LevelPlan {
    std::vector<LevelGen*> levels;
    LevelPlan() { }
    LevelPlan(const std::vector<LevelGen*>& v) : levels(v) { }

    static const LevelPlan& basicPlan();
    static const LevelPlan& gnarlyPlan();
};

#endif
