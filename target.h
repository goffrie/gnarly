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

public:
    Target(int y, int x, int r);
    virtual void move(Direction d) override;
    virtual void attack(Direction d) override;
    virtual void use(Direction d) override;
    virtual void skill(int i) override;
    virtual void restart() override;
    virtual void quit() override;
    virtual void confirm() override;
    virtual std::pair<int,int> getTarget();
};

#endif
