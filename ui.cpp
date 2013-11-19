#include "ui.h"

#include <cstdlib>

UI* UI::ui = 0;

UI* UI::instance() {
    return ui;
}

void UI::cleanup() {
    delete ui;
}

void UI::setInstance(UI* _ui) {
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        atexit(cleanup);
    }
    delete ui;
    ui = _ui;
}
