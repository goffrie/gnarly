#include "surface.h"

using namespace std;

// Provide useful default implementations.
void Surface::draw(int y, int x, const string& c) {
    for (int i = 0; i < c.size(); ++i) draw(y, x+i, c[i]);
}
void Surface::fillLine(int y, const string& c) {
    for (int i = 0; i < c.size(); ++i) draw(y, i, c[i]);
    // XXX hardcoded
    for (int i = c.size(); i < 79; ++i) draw(y, i, ' ');
}
