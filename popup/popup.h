#ifndef __POPUP_H__
#define __POPUP_H__

#include "displayable.h"
#include "commandhandler.h"
#include <string>
#include <vector>

// Represents a popup window that contains text
class PopUp : public Displayable {
    int y, x, height, width;
    // The offset of the y and x position to account for the margin and the border
    enum {
        ybuffer = 2,
        xbuffer = 2
    };
    // The text to display on the popup, divided into lines
    std::vector<std::string> text;

protected:
    // True indicates we close the popup
    bool submit;

    PopUp(const std::string& t, int y = 2, int x = 5, int height = 22, int width = 69);

public:
    virtual ~PopUp() {}
    // Changes the text on the popup
    virtual void setText(const std::string& t);
    virtual void draw(Surface& target) const override;
    // Creates and manages a popup with the given text, pausing the gmae
    static void make(const std::string& t);
};

#endif
