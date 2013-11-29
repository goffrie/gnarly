#include "inventory.h"
#include "inventorypopup.h"
#include "ui.h"
#include "item.h"
#include "language.h"
#include <sstream>
#include <iomanip>

using namespace std;

string InventoryPopUp::getText(const Inventory& items) {
    ostringstream txt;
    txt << "Inventory:" << endl;
    bool newLine = false;
    for (Inventory::const_iterator p = items.begin(); p != items.end(); ++p) {
        txt << '<' << p->first << '>' << ": " << left << setw(25) << p->second->name(NoArticle);
        if (newLine) {
            txt << endl;
            newLine = false;
        } else {
            newLine = true;
        }
    }
    return txt.str();
}

void InventoryPopUp::make(Player& p, Inventory& inv) {
    InventoryPopUp pop(getText(inv));
    pop.draw(*UI::instance());
    UI::instance()->redraw();
    while (!pop.submit) {
        UI::instance()->clearMsg();
        int ch = UI::instance()->readChar();
        switch (ch) {
            case ' ':
            case 's':
                pop.submit = true;
                break;
            default:
                if (inv.useItem(p, ch)) {
                    pop.setText(getText(inv));
                    pop.draw(*UI::instance());
                    UI::instance()->redraw();
                } else {
                    UI::instance()->say("Not a valid item.");
                }
        }
    }
}
