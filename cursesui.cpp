#include "cursesui.h"

#include <ncurses.h>
#include <cctype>

using namespace std;

inline Direction viKey(int c) {
    switch (c) {
        case 'h': return WEST;
        case 'j': return SOUTH;
        case 'k': return NORTH;
        case 'l': return EAST;
        case 'y': return NW;
        case 'u': return NE;
        case 'b': return SW;
        case 'n': return SE;
        case KEY_UP: return NORTH;
        case KEY_DOWN: return SOUTH;
        case KEY_LEFT: return WEST;
        case KEY_RIGHT: return EAST;
        case KEY_A1: return NW;
        case KEY_A3: return NE;
        case KEY_C1: return SW;
        case KEY_C3: return SE;
    }

    return INVALID_DIRECTION;
}

CursesUI::CursesUI() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

CursesUI::~CursesUI() {
    endwin();
}

void CursesUI::queryCommand(CommandHandler& target) {
    switch (int c = readChar()) {
        case 'h': case 'j': case 'k': case 'l':
        case 'y': case 'u': case 'b': case 'n':
        case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT:
        case KEY_A1: case KEY_A3: case KEY_C1: case KEY_C3:
            target.move(viKey(c));
            break;
        case 'a': {
            int a = readChar();
            Direction d = viKey(a);
            if (d == INVALID_DIRECTION) {
                string msg = "Unknown direction ";
                msg += a;
                msg += "!";
                say(msg.c_str());
            } else {
                target.attack(d);
            }
            break;
        }
        case 'q': { // quaff
            // XXX
            int a = readChar();
            Direction d = viKey(a);
            if (d == INVALID_DIRECTION) {
                string msg = "Unknown direction ";
                msg += a;
                msg += "!";
                say(msg.c_str());
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
        default: {
            string msg = "Unknown command ";
            msg += c;
            msg += "!";
            say(msg.c_str());
        }
    }
}

void CursesUI::say(const char* msg) {
    mvaddstr(29, 0, msg);
    clrtoeol();
}

int CursesUI::readChar() {
    return getch();
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
