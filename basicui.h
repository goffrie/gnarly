#ifndef __BASIC_UI_H__
#define __BASIC_UI_H__

#include <string>
#include <vector>
#include "ui.h"

class BasicUI : public UI {
    std::vector<std::string> screen;
    std::string message;

public:
    BasicUI();
    virtual ~BasicUI() override;
    virtual void queryCommand(CommandHandler& target) override;
    virtual void say(const std::string& msg) override;
    virtual int readChar() override;
    virtual std::string readLine() override;
    std::string readNext();
    virtual void draw(int y, int x, char c) override;
    virtual void draw(int y, int x, const std::string& str) override;
    virtual void fillLine(int y, const std::string& str) override;
    virtual void redraw() override;
};

#endif
