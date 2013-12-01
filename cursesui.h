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
    virtual ~CursesUI() override;

    // Unlike BasicUI, CursesUI can support colors and dimming
    virtual void setColor(int foreground, int background) override;
    virtual void unsetColor(int foreground, int background) override;
    virtual void setDim() override;
    virtual void unsetDim() override;

    // See description in the UI and surface class
    virtual void clearMsg() override;
    virtual void queryCommand(CommandHandler& target) override;
    virtual void say(const std::string& msg) override;
    virtual int readChar() override;
    virtual std::string readLine() override;
    virtual void draw(int y, int x, char c) override;
    virtual void draw(int y, int x, const std::string& str) override;
    virtual void fillLine(int y, const std::string& str) override;
    virtual void cursor(int y, int x) override;
    virtual void redraw() override;
};

#endif
