#ifndef __POPUP_H__
#define __POPUP_H__

#include "displayable.h"
#include <string>
#include <vector>

// XXX I would make a baser class for this, but i'm not sure what use a more generic window would be
class PopUp : public Displayable {
    int y, x, height, width;
    enum {
        ybuffer = 2,
        xbuffer = 2
    };
    std::vector<std::string> text;

public:
    PopUp(const std::string& t, int y, int x, int height, int width);
    virtual ~PopUp() {}
    virtual void draw(Surface& target) const override;
};

#endif
