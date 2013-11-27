#include "popupcreator.h"
#include <sstream>
#include "wizard.h"
#include "paladin.h"
#include "thief.h"
#include "skill.h"
#include <vector>

using namespace std;

void PopUpCreator::victory(int score) {
    ostringstream line;

    line << "You Win \\(^o^)/ You saved the world! As soon as you succeed, people start reconsidering their lives. "
         "War ceases to exist and people learn to empathize with each other, and scarcity is solved.  "
         "Everyone lives happily ever after. The end.\n\n"
         "Score: " << score;
    PopUp::make(line.str());
}

void PopUpCreator::defeat(int score) {
    ostringstream line;

    line << "You Died x.x After failing to stop the monsters, they escaped to the surface. "
         "Nations fell before the neverending stream of monsters, and after countless years "
         "of struggle the entire world was devoured. Nothing ever lived ever again. The end.\n\n"
         "On the upside, you got " << score << " points!";
    PopUp::make(line.str());
}

void PopUpCreator::tutorial() {
    controlTutorial();
    classTutorial();
}

void PopUpCreator::controlTutorial() {
    ostringstream line;

    line << " Movement/Direction:             Attack: 'a' + direction\n"
            "|--------|--------|---------|\n"
            "|y / 7   |k/8/UP  |u / 9    |    Use Potion: 'q' + direction\n"
            "| NW     | North  | NE      |\n"
            "|--------|--------|---------|    Use Skill: '!', '@', '#' + \n"
            "|h/4/LEFT|        |l/6/RIGHT|       (optionally) Target\n"
            "| West   |        | East    |\n"
            "|--------|--------|---------|    Quit: 'Q'\n"
            "|b / 1   |j/2/DOWN|n / 3    |\n"
            "| SW     | South  | SE      |    Restart: 'R'\n"
            "|--------|--------|---------|\n"
            "\n"
            "When a skill requires targeting, you enter targeting mode. Then, use direction keys to select target, and <space> to confirm";
    PopUp::make(line.str());
}

void PopUpCreator::classTutorial() {
    ostringstream line;
    line << "Classes:\n";
    Wizard w;
    line << "     Wizard:\n";
    vector<Skill*> skills = w.getSkills();
    for (unsigned int i = 0; i < skills.size(); i++) {
        line << "        " << skills[i]->name() << ": " << skills[i]->description() << endl;
    }
    line << endl;
    Paladin p;
    line << "     Paladin:\n";
    skills = p.getSkills();
    for (unsigned int i = 0; i < skills.size(); i++) {
        line << "        " << skills[i]->name() << ": " << skills[i]->description() << endl;
    }
    line << endl;
    Thief t;
    line << "     Thief:\n";
    skills = t.getSkills();
    for (unsigned int i = 0; i < skills.size(); i++) {
        line << "        " << skills[i]->name() << ": " << skills[i]->description() << endl;
    }
    PopUp::make(line.str());
}
