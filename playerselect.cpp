#include "playerselect.h"
#include "ui.h"
#include "player.h"
#include "commandargs.h"
#include "humanplayer.h"
#include "elfplayer.h"
#include "dwarfplayer.h"
#include "orcplayer.h"
#include "superelf.h"
#include "game.h"

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
    switch (c) {
        case Elf: return new ElfPlayer();
        case Orc: return new OrcPlayer();
        case Human: return new HumanPlayer();
        case Dwarf: return new DwarfPlayer();
        case SuperElf:
            if (dev) {
                return new SuperElfPlayer();
            }
        default:
            cout << "Quitting..." << endl;
            return 0;
    }
}

Player* PlayerSelect::getPlayer(UI& ui) {
    if (!gnarly) {
        return getBasicPlayer();
    }
    player = new HumanPlayer();
    curs_set(0);
    int c;
    while (true) {
        draw(ui);
        ui.redraw();
        c = ui.readChar();
        switch (c) {
            case Elf:
                delete player;
                player = new ElfPlayer();
                break;
            case Orc:
                delete player;
                player = new OrcPlayer();
                break;
            case Human:
                delete player;
                player = new HumanPlayer();
                break;
            case Dwarf:
                delete player;
                player = new DwarfPlayer();
                break;
            case SuperElf:
                if (dev) {
                    delete player;
                    player = new SuperElfPlayer();
                    break;
                }
            case ' ':
                curs_set(1);
                return player;
            case 'q':
                delete player;
                return 0;
            default:
                continue;
        }
    }
}                                              

void PlayerSelect::draw(Surface& target) const {
    target.setColor(COLOR_RED, COLOR_BLACK);
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
    target.fillLine(12, "      -       ##=;-=======   ;XX ===-;.  ##,# # =-=;==;;===###=####-    ");
    target.fillLine(13, "     X ###  =##==;-.=-=-=-==-= x# =--+X###+#X+ ==,;-==;-==-+##,####X=   ");
    target.fillLine(14, "    . =.=X#x+#=--;-.-;,========.#..x+##x..x..=-=-=;===;====#=+######;    ");
    target.fillLine(15, "   +#x,=;X##+==,,= -.,+x====;===.#-X= - ;= ;, ==-;==-=;===-+# x#=X###=   ");
    target.fillLine(16, "  #+#,.=XX=x= - === x+##X====-= = =.   =.==,=.-===.;==;=.=;=,###+#####   ");
    target.fillLine(17, " ,-#=,===X - ===.=;   ,# ;=====    .=,==  .;==-  ==.====    x-####-##x   ");
    target.fillLine(18, "=,# . - ==    ===       .. ===        =. =- ==    -.  =        ## X,#;   ");

    target.unsetColor(COLOR_RED, COLOR_BLACK);
    target.fillLine(19, "");
    target.fillLine(20, "");
    ostringstream line;
    string n = player->name();
    n[0] = toupper(n[0]);
    line << "    Currently: " << n << "       Press <Space> to Begin, <q> to quit";
    target.fillLine(21, line.str());
    target.fillLine(22, "");
    target.setColor(COLOR_GREEN, COLOR_BLACK);
    target.fillLine(23, "Choose your race:");
    target.fillLine(24, "Easy - Elf <e>, Easy - Orc <o>, Normal - Human <h>, Hard - Dwarf <d>");
    target.unsetColor(COLOR_GREEN, COLOR_BLACK);
}
