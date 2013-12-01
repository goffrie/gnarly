#ifndef __POPUPCREATOR_H__
#define __POPUPCREATOR_H__

#include "popup.h"

// Used to create a variety of different popups
class PopUpCreator {
private:
    // Various tutorial popups
    static void controlTutorial();
    static void raceTutorial();
    static void classTutorial();

public:
    // Popups for winning, losing, and reaching a new level resectively
    static void victory(int score);
    static void defeat(int score);
    static void level(int l);
    // Displays all tutorial popups
    static void tutorial();
};

#endif
