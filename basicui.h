#ifndef __BASIC_UI_H__
#define __BASIC_UI_H__

#include <string>
#include <vector>
#include "ui.h"

// The basic UI that accepts command line input and reprints the whole screen
// each time it is redrawn
class BasicUI : public UI {
    // The screen and message that will be drawn when redraw is called
    std::vector<std::string> screen;
    std::string message;

    // A convenience function that reads in a string from input
    std::string readNext();
public:
    BasicUI();
    virtual ~BasicUI();
    // See description in the UI and surface class
    virtual void queryCommand(CommandHandler& target);
    virtual void say(const std::string& msg);
    virtual int readChar();
    virtual std::string readLine();
    virtual void draw(int y, int x, char c);
    virtual void draw(int y, int x, const std::string& str);
    virtual void fillLine(int y, const std::string& str);
    virtual void redraw();
};

#endif
