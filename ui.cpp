#include "ui.h"

#include <cstdlib>

UI* UI::ui = 0;

UI* UI::instance() {
    return ui;
}

void UI::setInstance(UI* _ui) {
    delete ui;
    ui = _ui;
}
