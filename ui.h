#ifndef __UI_H__
#define __UI_H__

#include "commandhandler.h"
#include "surface.h"

#include <string>

// An abstract class for input/output, to provide pluggable implementations.
class UI : public Surface {
public:
    virtual ~UI() { }

    // Clears the bottom message list, instead of adding the next message to it
    virtual void clearMsg() { }

    // Ask for (and wait on) a command from the user.
    virtual void queryCommand(CommandHandler& target) = 0;

    // Write a message to the user.
    virtual void say(const std::string& msg) = 0;
    // Read one (non-space) character.
    virtual int readChar() = 0;
    // Read a line. Always call `say` first, to prompt the user.
    virtual std::string readLine() = 0;

    // Refreshes the display (by reprinting or curses)
    virtual void redraw() = 0;

// A kind of singleton, where the instance is chosen at runtime.
private:
    static UI* ui;
public:
    static UI* instance();
    // Sets the instance to a certain type of display
    static void setInstance(UI* ui);
};

#endif
