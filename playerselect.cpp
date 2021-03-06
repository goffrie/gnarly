#include "playerselect.h"
#include "ui.h"
#include "player.h"
#include "commandargs.h"
#include "humanplayer.h"
#include "elfplayer.h"
#include "dwarfplayer.h"
#include "halflingplayer.h"
#include "orcplayer.h"
#include "superelf.h"
#include "game.h"
#include "class.h"
#include "thief.h"
#include "paladin.h"
#include "wizard.h"
#include "util.h"
#include "popupcreator.h"

#include <iostream>
#include <sstream>
#include <ncurses.h>

using namespace std;

PlayerSelect::PlayerSelect() : Displayable(), player(0) {
}

Player* PlayerSelect::getBasicPlayer() {
    cout << "Choose your race: " << endl;
    cout << "(Easy - Elf (e), Easy - Orc(o), Normal - Human (h), Hard - Dwarf (d))" << endl;
    char c;
    cin >> c;
    Player* p;
    switch (c) {
        case Elf: p = new ElfPlayer(); p->setClass(new Class); return p;
        case Orc: p = new OrcPlayer(); p->setClass(new Class); return p;
        case Human: p = new HumanPlayer(); p->setClass(new Class); return p;
        case Dwarf: p = new DwarfPlayer(); p->setClass(new Class); return p;
        case SuperElf:
            if (dev) {
                p = new SuperElfPlayer(); p->setClass(new Class); return p;
            }
        default:
            cout << "Quitting..." << endl;
            return 0;
    }
}

void PlayerSelect::swapPlayer(Player* p) {
    player->setClass(0);
    delete player;
    player = p;
    player->setClass(playerClass);
}

void PlayerSelect::swapClass(Class* c) {
    delete playerClass;
    playerClass = c;
    player->setClass(playerClass);
}

Player* PlayerSelect::getPlayer(UI& ui) {
    PlayerSelect ps;
    if (!gnarly) {
        return ps.getBasicPlayer();
    }
    // By default, players are human thieves
    ps.playerClass = new Thief();
    ps.player = new HumanPlayer();
    ps.player->setClass(ps.playerClass);

    curs_set(0);
    int c;
    while (true) {
        // Wait for input to decide what class and race for the player to be
        ps.draw(ui);
        ui.redraw();
        c = ui.readChar();
        switch (c) {
            case Elf:
                ps.swapPlayer(new ElfPlayer());
                break;
            case Orc:
                ps.swapPlayer(new OrcPlayer());
                break;
            case Human:
                ps.swapPlayer(new HumanPlayer());
                break;
            case Dwarf:
                ps.swapPlayer(new DwarfPlayer());
                break;
            case Halfling:
                ps.swapPlayer(new HalflingPlayer());
                break;
            case ThiefClass:
                ps.swapClass(new Thief());
                break;
            case PaladinClass:
                ps.swapClass(new Paladin());
                break;
            case WizardClass:
                ps.swapClass(new Wizard());
                break;
            case None:
                ps.swapClass(new Class());
                break;
            case SuperElf:
                if (dev) {
                    ps.swapPlayer(new SuperElfPlayer());
                }
                break;
            case '?':
                PopUpCreator::tutorial();
                break;
            case ' ': case 's':
                curs_set(1);
                return ps.player;
            case 'q':
                delete ps.player;
                return 0;
        }
    }
}

void PlayerSelect::draw(Surface& target) const {
    target.setColor(COLOR_RED, COLOR_BLACK);
    // What a beautiful drawing, right?
    target.fillLine(0, "   _____                          _                                      ");
    target.fillLine(1, "  / ____|                        | |                        ##           ");
    target.fillLine(2, " | |  __   _ __     __ _   _ __  | |  _   _               ;=x# ;         ");
    target.fillLine(3, " | | |_ | | '_ \\   / _` | | '__| | | | | | |             #### ..         ");
    target.fillLine(4, " | |__| | | | | | | (_| | | |    | | | |_| |           ###= ;=+          ");
    target.fillLine(5, "  \\_____| |_| |_|  \\__,_| |_|    |_|  \\__, |          ##  ====# +        ");
    target.fillLine(6, "                                       __/ |         x# .====+##,        ");
    target.fillLine(7, "                  ;+###          x# = |___/        ,-#,--===..###        ");
    target.fillLine(8, "                 xx#+.##-       +#+ =           X. ##++=-===  +#x        ");
    target.fillLine(9, "                 ##x;-=###      #x--==####x    #x##X+ ,=====-#####       ");
    target.fillLine(10, "                ##+==.==,####  #====-= ####,  #X;=x ,=== -=. X#;#x       ");
    target.fillLine(11, "               ##===;====.##.##;====-;-,####.#X# ,= ======= #x#####+     ");
    target.fillLine(12, "      -       ##=;-=======   ;XX ===-;.  ##,# # =-=;==;;===###=####-     ");
    target.fillLine(13, "     X ###  =##==;-.=-=-=-==-= x# =--+X###+#X+ ==,;-==;-==-+##,####X=    ");
    target.fillLine(14, "    . =.=X#x+#=--;-.-;,========.#..x+##x..x..=-=-=;===;====#=+######;    ");
    target.fillLine(15, "   +#x,=;X##+==,,= -.,+x====;===.#-X= - ;= ;, ==-;==-=;===-+# x#=X###=   ");
    target.fillLine(16, "  #+#,.=XX=x= - === x+##X====-= = =.   =.==,=.-===.;==;=.=;=,###+#####   ");
    target.fillLine(17, " ,-#=,===X - ===.=;   ,# ;=====    .=,==  .;==-  ==.====    x-####-##x   ");
    target.fillLine(18, "=,# . - ==    ===       .. ===        =. =- ==    -.  =        ## X,#;   ");

    target.unsetColor(COLOR_RED, COLOR_BLACK);
    target.fillLine(19, "");
    target.fillLine(20, "");
    ostringstream line;
    line << "  Currently: " << titleCase(player->name(NoArticle));
    target.fillLine(21, line.str());
    line.str("");
    line << "     Press <Space> to Begin, <q> to quit, <?> for help";
    target.fillLine(22, line.str());
    target.setColor(COLOR_GREEN, COLOR_BLACK);
    target.fillLine(23, "Choose your race:");
    target.fillLine(24, "Easy - Elf <e>, Easy - Orc <o>, Normal - Human <h>");
    target.fillLine(25, "Normal - Halfling <a>, Hard - Dwarf <d>");
    target.fillLine(26, "");
    target.fillLine(27, "Choose your class:");
    target.fillLine(28, "None <n>, Thief <t>, Paladin <p>, Wizard <w>");
    target.unsetColor(COLOR_GREEN, COLOR_BLACK);
}
