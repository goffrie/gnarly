#include "popup.h"
#include "surface.h"
#include "util.h"
#include "ui.h"

#include <curses.h>
#include <cassert>
#include <iostream>
using namespace std;

PopUp::PopUp(const string& t, int y, int x, int h, int w) :
  y(y), x(x), height(h), width(w), text(getLines(t, w - xbuffer * 2)), submit(false) {
}

void PopUp::setText(const std::string& t) {
    text = getLines(t, width - xbuffer * 2);
}

void PopUp::draw(Surface& target) const {
    assert(text.size() < (unsigned)(height - ybuffer * 2 - 2));
    target.setColor(COLOR_BLUE, COLOR_BLACK);
    for (int dy = y; dy < y + height; dy++) {
        for (int dx = x; dx < x + width; dx++) {
            char c = ' ';
            if (y == dy || x == dx || dy == y + height - 1 || dx == x + width - 1) {
                c = '#';
            }
            target.draw(dy, dx, c);
        }
    }
    target.unsetColor(COLOR_BLUE, COLOR_BLACK);
    for (unsigned int i = 0; i < text.size(); i++) {
        target.draw(y + i + ybuffer, x + xbuffer, text[i]);
    }
    target.draw(y + height - ybuffer - 1, x + xbuffer, "Press <space>/<s> to dismiss.");
}

void PopUp::make(const string& t) {
    PopUp p(t);
    p.draw(*UI::instance());
    UI::instance()->redraw();
    while (!p.submit) {
        switch (UI::instance()->readChar()) {
            case ' ':
                p.submit = true;
                break;
            case 's':
                p.submit = true;
                break;
        }
    }
}
