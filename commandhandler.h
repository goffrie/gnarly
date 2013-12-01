#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include "direction.h"

// Abstract class that represents something commands can be sent to
// Used by UI as a target for commands
class CommandHandler {
public:
    // What these do depends on exactly what class it is, so go to
    // a specific class for description
    virtual void move(Direction d) = 0;
    virtual void attack(Direction d) = 0;
    virtual void use(Direction d) = 0;
    virtual void skill(int i) = 0;
    virtual void inventory() = 0;
    virtual void restart() = 0;
    virtual void quit() = 0;
    virtual void confirm() = 0;
};

#endif
