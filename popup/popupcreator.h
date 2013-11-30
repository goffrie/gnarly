#ifndef __POPUPCREATOR_H__
#define __POPUPCREATOR_H__

#include "popup.h"

class PopUpCreator {
public:
    static void victory(int score);
    static void defeat(int score);
    static void level(int l);
    static void tutorial();
    static void controlTutorial();
    static void raceTutorial();
    static void classTutorial();
};

#endif
