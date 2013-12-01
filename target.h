#ifndef __TARGET_H__
#define __TARGET_H__

#include "commandhandler.h"
#include <utility>

class Target : public CommandHandler {
    int startY, startX;
    int y, x;
    int range;
    bool _quit;
    bool submit;

    Target(int y, int x, int r);
public:
    virtual void move(Direction d) override;
    virtual void attack(Direction d) override;
    virtual void use(Direction d) override;
    virtual void skill(int i) override;
    virtual void inventory() override;
    virtual void restart() override;
    virtual void quit() override;
    virtual void confirm() override;
    static std::pair<int,int> getTarget(int y, int x, int r);
    static bool validTarget(std::pair<int,int> p);
};

#endif
