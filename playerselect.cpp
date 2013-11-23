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

void PlayerSelect::draw(UI& ui) const {
    ui.setColor(COLOR_RED, COLOR_BLACK);
    ui.fillLine(0, "   _____                          _                                      ");
    ui.fillLine(1, "  / ____|                        | |                        ##           ");
    ui.fillLine(2, " | |  __   _ __     __ _   _ __  | |  _   _               ;=x# ;         ");
    ui.fillLine(3, " | | |_ | | '_ \\   / _` | | '__| | | | | | |             #### ..         ");
    ui.fillLine(4, " | |__| | | | | | | (_| | | |    | | | |_| |           ###= ;=+          ");
    ui.fillLine(5, "  \\_____| |_| |_|  \\__,_| |_|    |_|  \\__, |          ##  ====# +        ");
    ui.fillLine(6, "                                       __/ |         x# .====+##,        ");
    ui.fillLine(7, "                  ;+###          x# = |___/        ,-#,--===..###        ");
    ui.fillLine(8, "                 xx#+.##-       +#+ =           X. ##++=-===  +#x        ");
    ui.fillLine(9, "                 ##x;-=###      #x--==####x    #x##X+ ,=====-#####       ");
    ui.fillLine(10, "                ##+==.==,####  #====-= ####,  #X;=x ,=== -=. X#;#x       ");
    ui.fillLine(11, "               ##===;====.##.##;====-;-,####.#X# ,= ======= #x#####+     ");
    ui.fillLine(12, "      -       ##=;-=======   ;XX ===-;.  ##,# # =-=;==;;===###=####-    ");
    ui.fillLine(13, "     X ###  =##==;-.=-=-=-==-= x# =--+X###+#X+ ==,;-==;-==-+##,####X=   ");
    ui.fillLine(14, "    . =.=X#x+#=--;-.-;,========.#..x+##x..x..=-=-=;===;====#=+######;    ");
    ui.fillLine(15, "   +#x,=;X##+==,,= -.,+x====;===.#-X= - ;= ;, ==-;==-=;===-+# x#=X###=   ");
    ui.fillLine(16, "  #+#,.=XX=x= - === x+##X====-= = =.   =.==,=.-===.;==;=.=;=,###+#####   ");
    ui.fillLine(17, " ,-#=,===X - ===.=;   ,# ;=====    .=,==  .;==-  ==.====    x-####-##x   ");
    ui.fillLine(18, "=,# . - ==    ===       .. ===        =. =- ==    -.  =        ## X,#;   ");

    ui.unsetColor(COLOR_RED, COLOR_BLACK);
    ui.fillLine(19, "");
    ui.fillLine(20, "");
    ostringstream line;
    string n = player->name();
    n[0] = toupper(n[0]);
    line << "    Currently: " << n << "       Press <Space> to Begin, <q> to quit";
    ui.fillLine(21, line.str());
    ui.fillLine(22, "");
    ui.setColor(COLOR_GREEN, COLOR_BLACK);
    ui.fillLine(23, "Choose your race:");
    ui.fillLine(24, "Easy - Elf <e>, Easy - Orc <o>, Normal - Human <h>, Hard - Dwarf <d>");
    ui.unsetColor(COLOR_GREEN, COLOR_BLACK);
}
