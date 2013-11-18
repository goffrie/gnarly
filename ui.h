#ifndef __UI_H__
#define __UI_H__

#include "util.h"
#include "commandhandler.h"

#include <string>

// An abstract class for input/output, to provide pluggable implementations.
class UI {
public:
    virtual ~UI() {};
    // Initialize what need to be
    virtual void init() = 0;

    // Ask for (and wait on) a command from the user.
    virtual void queryCommand(CommandHandler& target) = 0;

    // Write a message to the user.
    virtual void say(const char* msg) = 0;
    // Read one (non-space) character.
    virtual char readChar() = 0;
    // Read a line. Always call `say` first, to prompt the user.
    virtual std::string readLine() = 0;

    // Draw a tile at the given location.
    virtual void draw(int y, int x, char c) = 0;
    // Or a string.
    virtual void draw(int y, int x, const std::string& c) = 0;
    // Refreshes the display (by reprinting or curses)
    virtual void redraw() = 0;
};

#endif
