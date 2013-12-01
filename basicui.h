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
    virtual ~BasicUI() override;
    // See description in the UI and surface class
    virtual void queryCommand(CommandHandler& target) override;
    virtual void say(const std::string& msg) override;
    virtual int readChar() override;
    virtual std::string readLine() override;
    virtual void draw(int y, int x, char c) override;
    virtual void draw(int y, int x, const std::string& str) override;
    virtual void fillLine(int y, const std::string& str) override;
    virtual void redraw() override;
};

#endif
