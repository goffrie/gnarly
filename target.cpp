#include "target.h"
#include "ui.h"

#include <stdlib.h>
#include <algorithm>

using namespace std;

Target::Target(int y, int x, int r) : startY(y), startX(x), y(y), x(x), range(r), _quit(false), submit(false) {
    UI::instance()->say("Beginning targeting");
}

void Target::move(Direction d) {
    if (max(abs(startY - y - d.dy()), abs(startX - x - d.dx())) > range) {
        return UI::instance()->say("Out of range");
    }
    y += d.dy();
    x += d.dx();
}

void Target::attack(Direction d) {
    UI::instance()->say("Currently targeting, press Q to quit");
}

void Target::use(Direction d) {
    UI::instance()->say("Currently targeting, press Q to quit");
}

void Target::skill(int i) {
    UI::instance()->say("Currently targeting, press Q to quit");
}

void Target::restart() {
    UI::instance()->say("Currently targeting, press Q to quit");
}

void Target::inventory() {
    UI::instance()->say("Currently targeting, press Q to quit");
}

void Target::quit() {
    _quit = true;
}

void Target::confirm() {
    submit = true;
}

pair<int,int> Target::getTarget(int y, int x, int r) {
    Target t(y, x, r);
    while (!t._quit) {
        UI::instance()->cursor(t.y, t.x);
        if (t.submit) {
            return make_pair(t.y, t.x);
        }
        UI::instance()->queryCommand(t);
    }
    return make_pair(-1, -1);
}

bool Target::validTarget(pair<int,int> p) {
    return !(p.first == -1 && p.second == -1);
}
