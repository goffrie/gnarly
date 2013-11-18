#include "basicui.h"

#include <iostream>
#include <cctype>

using namespace std;

inline Direction convert(string s) {
    if (s == "no") {
        return NORTH;
    } else if (s == "so") {
        return SOUTH;
    } else if (s == "ea") {
        return EAST;
    } else if (s == "we") {
        return WEST;
    } else if (s == "ne") {
        return NE;
    } else if (s == "nw") {
        return NW;
    } else if (s == "se") {
        return SE;
    } else if (s == "sw") {
        return SW;
    }

    return INVALID_DIRECTION;
}

BasicUI::BasicUI() {
    for (int y = 0; y < 30; y++) {
        string s(79, '_');
        screen.push_back(s);
    }
}

void BasicUI::init() {
}

BasicUI::~BasicUI() {

}

void BasicUI::queryCommand(CommandHandler& target) {
    string s = readNext();
    if (convert(s) != INVALID_DIRECTION) {
        target.move(convert(s));
    } else if (s == "a") {
        string a = readNext();
        Direction d = convert(a);
        if (d == INVALID_DIRECTION) {
            string msg = "Unknown direction " + a + "!";
            say(msg.c_str());
        } else {
            target.attack(d);
        }
    } else if (s == "u") {
        string u = readNext();
        Direction d = convert(u);
        if (d == INVALID_DIRECTION) {
            string msg = "Unknown direction " + u + "!";
            say(msg.c_str());
        } else {
            target.use(d);
        }
    } else if (s == "r") {
        say("Really restart? [yes/no] ");
        if (readNext() == "yes") target.restart();
    } else if (s == "q") {
        say("Really quit? [yes/no] ");
        if (readNext() == "yes") target.quit();
    } else {
        say(("Unknown command " + s + "!").c_str());
    }
}

void BasicUI::say(const char* msg) {
    draw(29, 0, msg);
    redraw();
}

char BasicUI::readChar() {
    char c;
    cin >> c;
    return c;
}

string BasicUI::readNext() {
    string s;
    cin >> s;
    return s;
}

string BasicUI::readLine() {
    string s;
    getline(cin, s);
    return s;
}

void BasicUI::draw(int y, int x, char c) {
    screen[y][x] = c;
}

void BasicUI::draw(int y, int x, const std::string& str) {
    screen[y].replace(x, string::npos, str);
}

void BasicUI::redraw() {
    for (unsigned y = 0; y < screen.size(); y++) {
        cout << screen[y] << endl;
    }
}
