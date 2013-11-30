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

    line << "As you smash the second altar, all the monsters immediately turn to dust. You arise from the cave (after "
         "spending the next month trying to find your way back up) to the cheers and surprise of your village! It "
         "turns out that the merchant's guild summoned the monsters to drive up the price of weapons, then sell "
         "them for exorbitant prices. You saved the world and destroyed the capitalist plot!\n\n"
         "Score: " << score;
    PopUp::make(line.str());
}

void PopUpCreator::defeat(int score) {
    ostringstream line;

    line << "You died, but honestly, no one in your village actually expected you to succeed. They had all fled to "
         "other continents and used you to distract the monsters until they could escape. So in a way, you "
         "succeeded! But not really.\n\n"
         "On the upside, you got " << score << " points!";
    PopUp::make(line.str());
}

void PopUpCreator::level(int l) {
    ostringstream line;

    switch(l) {
        case 1:
            line << "One month ago, monsters long thought extinct began appearing around your town. As more and more "
                "powerful monsters attacked the surface, some explorers found the entrace to the cave. It was decided "
                "that the most dashing, cunning, and powerful fighter would be sent to assault it. Unfortunately, you "
                "were the only fighter around. After days of travel, you enter the cave.";
            break;
        case 2:
            line << "After days of near-constant fighting, you manage to descend to the next level. Instead of another "
                "dungeon, you find yourself in a giant cave. You notice that as you descend further into the earth, the "
                "monsters seem to become stronger. You also notice that merchant's guild has somehow gained a "
                "monopoly on all trade within the monster economy.";
            break;
        case 3:
            line << "Weeks pass before you find the staircase to the next level, and after climbing down for half an hour, you "
                "find a small town with an artificial sun overhead. Somehow, the merchant lobbyists managed to "
                "convince the nonexistent monster government that creating a town would stabilize the economy and "
                "build a stronger sense of community.";
            break;
        case 4:
            line << "The next floor, you find a forest. \"How the fuck did they manage to grow a forest a kilometer "
                "underground?\" you ask. \"Why is the Aztec god that created mankind here, and why are there several "
                "copies of him?\" Unfortunately, merchants are too busy haggling over the prices of human blood to "
                "reply, and none of the monsters can speak human.";
            break;
        default:
            line << "After getting lost in the forest several times, and descending the next staircase for a full hour, you find "
                "yourself in a huge cavern flanked by two altars. Merchants surround the altars, but scurry away as soon "
                "as they see you. On the upside, it appears you've found the source of the monsters and just need to "
                "destroy the altars. On the downside, you've found the source of the monsters and are now surrounded by them.";
    }
    PopUp::make(line.str());
}

void PopUpCreator::tutorial() {
    controlTutorial();
    raceTutorial();
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

void PopUpCreator::raceTutorial() {
    ostringstream line;
    line << "Races:\n"
            "     Human: 50% increased score, average stats\n"
            "     Orc: Higher stats, half gold\n"
            "     Elf: High attack, low defence, potions are always positive\n"
            "     Dwarf: Weak stats, but double gold\n"
            "     Halfling: Weak stats, but dodges 20% of attacks\n";
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
