#ifndef __TARGET_H__
#define __TARGET_H__

#include "commandhandler.h"
#include <utility>

// A class used to get a target for a spell or ability
class Target : public CommandHandler {
    // The y and x position targeting started at
    int startY, startX;
    // The current targeting x and y position
    int y, x;
    // The range of targeting
    int range;
    // Whether or not it should quit/submit instead of continuing targeting
    bool _quit;
    bool submit;

    Target(int y, int x, int r);
public:
    // Move the target
    virtual void move(Direction d) override;
    // All of the following do nothing
    virtual void attack(Direction d) override;
    virtual void use(Direction d) override;
    virtual void skill(int i) override;
    virtual void wait() override;
    virtual void inventory() override;
    virtual void restart() override;
    // Cancel targeting
    virtual void quit() override;
    // Submit current target position
    virtual void confirm() override;
    // Returns a target, given starting y, x, and range
    static std::pair<int,int> getTarget(int y, int x, int r);
    // Returns whether something is a valid target
    static bool validTarget(std::pair<int,int> p);
};

#endif
