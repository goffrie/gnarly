#include "cursesui.h"

#include <ncurses.h>
#include <cctype>
#include <cassert>

using namespace std;

// The maximum allowed number of characters in the current
// message line, not including the " --more--"
const int maxMsgLineLength = 70;

inline Direction viKey(char c) {
    switch (c) {
        case 'h': return WEST;
        case 'j': return SOUTH;
        case 'k': return NORTH;
        case 'l': return EAST;
        case 'y': return NW;
        case 'u': return NE;
        case 'b': return SW;
        case 'n': return SE;
    }

    return INVALID_DIRECTION;
}

CursesUI::CursesUI() : msgLineLength(0) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

CursesUI::~CursesUI() {
    endwin();
}

void CursesUI::queryCommand(CommandHandler& target) {
    msgLineLength = 0;
    switch (char c = readChar()) {
        case 'h': case 'j': case 'k': case 'l':
        case 'y': case 'u': case 'b': case 'n':
            target.move(viKey(c));
            break;
        case 'a': {
            char a = readChar();
            Direction d = viKey(a);
            if (d == INVALID_DIRECTION) {
                say(string("Unknown direction ") + a + "!");
            } else {
                target.attack(d);
            }
            break;
        }
        case 'q': { // quaff
            // XXX
            char a = readChar();
            Direction d = viKey(a);
            if (d == INVALID_DIRECTION) {
                say(string("Unknown direction ") + a + "!");
            } else {
                target.use(d);
            }
            break;
        }
        case 'R': // restart
            say("Really restart? [yes/no] ");
            if (readLine() == "yes") {
                target.restart();
            } else {
                say("Never mind.");
            }
            break;
        case 'Q': // quit
            say("Really quit? [yes/no] ");
            if (readLine() == "yes") {
                target.quit();
            } else {
                say("Never mind.");
            }
            break;
        default:
            say(string("Unknown command ") + c + "!");
    }
}

void CursesUI::say(const std::string& msg) {
    assert(msg.size() <= maxMsgLineLength);
    if (msgLineLength + msg.size() > maxMsgLineLength) {
        mvaddstr(29, msgLineLength, " --more--");
        clrtoeol();
        while (getch() != '\n');
        msgLineLength = 0;
    }

    // Leave a space between messages.
    if (msgLineLength) ++msgLineLength;

    mvaddstr(29, msgLineLength, msg.c_str());
    msgLineLength += msg.size();
    clrtoeol();
}

char CursesUI::readChar() {
    while (1) {
        char c = getch();
        if (!isspace(c)) {
            return c;
        }
    }
}

string CursesUI::readLine() {
    string r;
    // Turn echo back on.
    echo();
    noraw();
    // Read the string.
    while (1) {
        char c = getch();
        if (c == '\n') break;
        r += c;
    }
    // Turn echo back off.
    raw();
    noecho();
    return r;
}

void CursesUI::draw(int y, int x, char c) {
    mvaddch(y, x, c);
}

void CursesUI::draw(int y, int x, const std::string& str) {
    mvaddstr(y, x, str.c_str());
}

void CursesUI::fillLine(int y, const std::string& str) {
    mvaddstr(y, 0, str.c_str());
    clrtoeol();
}

void CursesUI::cursor(int y, int x) {
    move(y, x);
}

void CursesUI::redraw() {
    refresh();
}
