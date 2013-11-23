#include "cursesui.h"

#include <ncurses.h>
#include <cctype>
#include <cassert>

using namespace std;

// The maximum allowed number of characters in the current
// message line, not including the " --more--"
const int maxMsgLineLength = 70;

// Convert an ncurses key code into a printable representation.
string printable(int code) {
    if (code == 0) return "NULL";
    if (code >= 0 && code < 32) return string("^") + char('A' - 1 + code);
    if (code == ' ' /* 32 */) return string("(space)");
    if (code > 32 && code < 127) return string(1, char(code));
    return string("(unknown)");
}

CursesUI::CursesUI() : msgLineLength(0) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
}

CursesUI::~CursesUI() {
    endwin();
}

void CursesUI::queryCommand(CommandHandler& target) {
    msgLineLength = 0;
    switch (int c = readChar()) {
        case 'h': case 'j': case 'k': case 'l':
        case 'y': case 'u': case 'b': case 'n':
        case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT:
        case KEY_A1: case KEY_A3: case KEY_C1: case KEY_C3:
        case '1': case '2': case '3': case '4':
        case '6': case '7': case '8': case '9':
            target.move(Direction::get(c));
            break;
        case 'a': {
            int a = readChar();
            Direction d = Direction::get(a);
            if (!d.valid()) {
                say(string("Unknown direction ") + printable(a) + "!");
            } else {
                target.attack(d);
            }
            break;
        }
        case 'q': { // quaff
            // XXX
            int a = readChar();
            Direction d = Direction::get(a);
            if (!d.valid()) {
                say(string("Unknown direction ") + printable(a) + "!");
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
            say(string("Unknown command ") + printable(c) + "!");
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
