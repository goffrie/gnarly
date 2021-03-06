#include "inventory.h"
#include "inventorypopup.h"
#include "ui.h"
#include "item.h"
#include "language.h"
#include <sstream>
#include <iomanip>

using namespace std;

string InventoryPopUp::getText(const Inventory& items) {
    const int lines = 15;

    vector<string> names;
    for (Inventory::const_iterator p = items.begin(); p != items.end(); ++p) {
        // Generate all text to display for each item
        names.push_back(string("<") + p->first + ">: " + p->second->name(NoArticle));
    }
    ostringstream txt;
    txt << "Inventory:";
    for (int i = 0; i < lines; ++i) {
        txt << endl;
        // Add all the text we generated
        if (i + lines < (signed)names.size()) {
            txt << left << setw(30) << names[i] << names[i + lines];
        } else if (i < (signed)names.size()) {
            txt << names[i];
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
                // Player exists inventory
                pop.submit = true;
                break;
            default:
                if (inv.useItem(p, ch)) {
                    // Player is using an item
                    pop.setText(getText(inv));
                    pop.draw(*UI::instance());
                    UI::instance()->redraw();
                } else {
                    UI::instance()->say("Not a valid item.");
                }
        }
    }
}
