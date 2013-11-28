#include "inventory.h"
#include "inventorypopup.h"
#include "ui.h"
#include "item.h"
#include "language.h"
#include <sstream>

using namespace std;

void InventoryPopUp::make(Player* p, Inventory* inv) {
    vector<Item*> items = inv->getItems();
    ostringstream text;
    text << "Inventory:" << endl;
    for (unsigned int i = 0; i < items.size(); i += 2) {
        text << '<' << (char)(i + 'a') << '>' << ": " << items[i]->name(NoArticle);
        if (i + 1 < items.size()) {
            text << "             <" << (char)(i + 1 + 'a') << '>' << ": " << items[i]->name(NoArticle);
        }
        text << endl;
    }
    InventoryPopUp pop(text.str());
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
                    text.str("");
                    items = inv->getItems();
                    text << "Inventory:" << endl;
                    for (unsigned int i = 0; i < items.size(); i++) {
                        text << '<' << (char)(i + 'a') << '>' << ": " << items[i]->name(NoArticle) << endl;
                    }
                    pop.setText(text.str());
                    pop.draw(*UI::instance());
                    UI::instance()->redraw();
                } else {
                    UI::instance()->say("Not a valid item.");
                }
        }
    }
}
