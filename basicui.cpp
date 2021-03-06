#include "basicui.h"
#include "direction.h"
#include "skill.h"

#include <iostream>
#include <cctype>

using namespace std;

BasicUI::BasicUI() : message() {
    for (int y = 0; y < 30; y++) {
        screen.push_back(string(79, ' '));
    }
}

BasicUI::~BasicUI() {

}

void BasicUI::queryCommand(CommandHandler& target) {
    string s = readNext();
    if (Direction::basicGet(s).valid()) {
        target.move(Direction::basicGet(s));
    } else if (s == "a") {
        string a = readNext();
        Direction d = Direction::basicGet(a);
        if (!d.valid()) {
            string msg = "Unknown direction " + a + "!";
            say(msg);
        } else {
            target.attack(d);
        }
    } else if (s == "u") {
        string u = readNext();
        Direction d = Direction::basicGet(u);
        if (!d.valid()) {
            string msg = "Unknown direction " + u + "!";
            say(msg);
        } else {
            target.use(d);
        }
    } else if (s[0] == FirstSkill || s[0] == SecondSkill || s[0] == ThirdSkill || s[0] == FourthSkill) {
        target.skill(Skill::getSkillNumber(s[0]));
    } else if (s == "s") {
        target.confirm();
    } else if (s == "r") {
        say("Really restart? [yes/no] ");
        redraw();
        if (readNext() == "yes") target.restart();
    } else if (s == "q") {
        say("Really quit? [yes/no] ");
        redraw();
        if (readNext() == "yes") target.quit();
    } else {
        say("Unknown command " + s + "!");
    }
}

void BasicUI::say(const std::string& msg) {
    if (message.empty()) {
        message += "Action:";
    }
    message += " ";
    message += msg;
}

int BasicUI::readChar() {
    char c;
    cin >> c;
    return (int)c;
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
    screen[y].replace(x, str.size(), str);
}

void BasicUI::fillLine(int y, const std::string& str) {
    screen[y] = str;
    screen[y].resize(79, ' ');
}

void BasicUI::redraw() {
    draw(29, 0, message);
    for (unsigned y = 0; y < screen.size(); y++) {
        cout << screen[y] << endl;
    }
    screen[29].replace(0, string::npos, 79, 0);
    message.clear();
}
