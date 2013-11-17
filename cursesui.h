#ifndef __CURSES_UI_H__
#define __CURSES_UI_H__

#include "ui.h"

class CursesUI : public UI {
public:
    virtual void queryCommand(UI::CommandDelegate& target) override;
    virtual void say(const char* msg) override;
    virtual char readChar() override;
    virtual std::string readLine() override;
    virtual void draw(int y, int x, char c) override;
    virtual void draw(int y, int x, const std::string& str) override;
};

#endif