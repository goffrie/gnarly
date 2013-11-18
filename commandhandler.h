#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include "util.h"

class CommandHandler {
public:
    virtual void move(Direction d) = 0;
    virtual void attack(Direction d) = 0;
    virtual void use(Direction d) = 0;
    virtual void restart() = 0;
    virtual void quit() = 0;
};

#endif
