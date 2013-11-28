#include "inventory.h"
#include "inventorypopup.h"
#include "ui.h"
#include "item.h"
#include "language.h"
#include <sstream>
#include <iomanip>

using namespace std;

string InventoryPopUp::getText(vector<Item*> items) {
    ostringstream txt;
    txt << "Inventory:" << endl;
    for (unsigned int i = 0; i < items.size(); i += 2) {
        txt << '<' << (char)(i + 'a') << '>' << ": " << left << setw(25) << items[i]->name(NoArticle);
        if (i + 1 < items.size()) {
            txt << "<" << (char)(i + 1 + 'a') << '>' << ": " << left << setw(25) << items[i]->name(NoArticle);
        }
        txt << endl;
    }
    return txt.str();
}

void InventoryPopUp::make(Player* p, Inventory* inv) {
    vector<Item*> items = inv->getItems();
    InventoryPopUp pop(getText(items));
    pop.draw(*UI::instance());
    UI::instance()->redraw();
    while (!pop.submit) {
        UI::instance()->clearMsg();
        int ch = UI::instance()->readChar();
        switch (ch) {
            case ' ':
                pop.submit = true;
                break;
            case 's':
                pop.submit = true;
                break;
            default:
                if (inv->useItem(p, ch - 'a')) {
                    items = inv->getItems();
                    pop.setText(getText(items));
                    pop.draw(*UI::instance());
                    UI::instance()->redraw();
                } else {
                    UI::instance()->say("Not a valid item.");
                }
        }
    }
}
