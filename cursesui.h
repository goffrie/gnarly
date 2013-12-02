#ifndef __CURSES_UI_H__
#define __CURSES_UI_H__

#include "ui.h"

// The much better UI that uses the ncurses library
class CursesUI : public UI {
    // The current message length
    int msgLineLength;
    // The color index we store grey in, since it is not there by default
    int grey;

    Direction readDirection();
public:
    CursesUI();
    virtual ~CursesUI();

    // Unlike BasicUI, CursesUI can support colors and dimming
    virtual void setColor(int foreground, int background);
    virtual void unsetColor(int foreground, int background);
    virtual void setDim();
    virtual void unsetDim();

    // See description in the UI and surface class
    virtual void clearMsg();
    virtual void queryCommand(CommandHandler& target);
    virtual void say(const std::string& msg);
    virtual int readChar();
    virtual std::string readLine();
    virtual void draw(int y, int x, char c);
    virtual void draw(int y, int x, const std::string& str);
    virtual void fillLine(int y, const std::string& str);
    virtual void cursor(int y, int x);
    virtual void redraw();
};

#endif
