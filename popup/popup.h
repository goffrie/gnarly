#ifndef __POPUP_H__
#define __POPUP_H__

#include "displayable.h"
#include "commandhandler.h"
#include <string>
#include <vector>

// XXX I would make a baser class for this, but i'm not sure what use a more generic window would be
class PopUp : public Displayable, public CommandHandler {
    int y, x, height, width;
    enum {
        ybuffer = 2,
        xbuffer = 2
    };
    std::vector<std::string> text;
    bool submit;

    PopUp(const std::string& t, int y = 5, int x = 5, int height = 20, int width = 69);

public:
    virtual ~PopUp() {}
    virtual void move(Direction d) override;
    virtual void attack(Direction d) override;
    virtual void use(Direction d) override;
    virtual void skill(int i) override;
    virtual void restart() override;
    virtual void quit() override;
    virtual void confirm() override;
    virtual void draw(Surface& target) const override;
    static void make(const std::string& t);
};

#endif
