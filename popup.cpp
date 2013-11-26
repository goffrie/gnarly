#include "popup.h"
#include "surface.h"
#include "util.h"

#include <cassert>
#include <iostream>
using namespace std;

PopUp::PopUp(const string& t, int y, int x, int h, int w) :
  y(y), x(x), height(h), width(w), text(getLines(t,w - xbuffer * 2)) {

}

void PopUp::draw(Surface& target) const {
    assert(text.size() < (unsigned)(height - ybuffer * 2));
    for (int dy = y; dy < y + height; dy++) {
        for (int dx = x; dx < x + width; dx++) {
            char c = ' ';
            if (y == dy || x == dx || dy == y + height - 1 || dx == x + width - 1) {
                c = '=';
            }
            target.draw(dy, dx, c);
        }
    }
    for (unsigned int i = 0; i < text.size(); i++) {
        target.draw(y + i + ybuffer, x + xbuffer, text[i]);
    }
}
