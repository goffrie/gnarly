#include "popup.h"
#include "surface.h"

#include <cassert>
#include <iostream>
using namespace std;

PopUp::PopUp(const string& t, int y, int x, int h, int w) :
  y(y), x(x), height(h), width(w), text(getLines(t,w)) {

}

vector<string> PopUp::getLines(const string& t, int width) {
    vector<string> lines;
    unsigned int i = 0;
    while (i < t.size()) {
        string next = t.substr(i, width - xbuffer * 2);
        // Try to split it at the first newline, try to contain the entire string,
        // or try to split it at the last space, in that order

        if (next.find('\n') != string::npos) {
            // There is a newline
            int nextPos = next.find('\n');
            lines.push_back(next.substr(0, nextPos));
            i += nextPos + 1;
        } else if (i + width - xbuffer * 2 > t.size()) {
            lines.push_back(next);
            break;
        } else if (next.rfind(' ') != string::npos) {
            // There is a space
            int nextPos = next.rfind(' ');
            lines.push_back(next.substr(0, nextPos));
            i += nextPos + 1;
        } else {
            // There is no space
            next[next.size() - 1] = '-';
            lines.push_back(next);
            i += width - xbuffer * 2 - 1;
        }
    }
    return lines;
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
