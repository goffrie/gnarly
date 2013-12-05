#include "game.h"

#include "potion.h"
#include "gold.h"
#include "staircase.h"
#include "commandargs.h"
#include "playerselect.h"
#include "dungeon.h"
#include "playerstatus.h"
#include "cursesui.h"
#include "basicui.h"
#include "level.h"
#include "popupcreator.h"
#include "memory.h"
#include "target.h"
#include "itemadapter.h"
#include "levelobjectvisitor.h"

#include "levelgen/levelgen.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

const int lastLevel = 8;

Game* Game::_instance = 0;

Game::Game() : player(0), pstatus(0), level(0), mem(0), _quit(false), gameOver(false), _shouldRestart(false) {
    // Initialize the UI.
    if (gnarly) {
        UI::setInstance(new CursesUI());
    } else {
        UI::setInstance(new BasicUI());
    }

    // Do per-game initialization.
    Team::init();
    Potion::resetUsed();

    // Ask the user to select their player.
    player = PlayerSelect::getPlayer(*UI::instance());
    if (!player) {
        _quit = true;
        return;
    }

    // Initialize the display.
    pstatus = new PlayerStatus(*player);
    display.add(pstatus);
    display.add(player, 2);

    // Select the level plan.
    if (haveLayout) {
        plan = levelLayout;
    } else if (gnarly) {
        plan = LevelPlan::gnarlyPlan();
    } else {
        plan = LevelPlan::basicPlan();
    }

    // Set up the first dungeon level.
    dlvl = 0;
    makeNewLevel();
}

Game::~Game() {
    UI::setInstance(0);
    delete pstatus;
    delete player;
    delete level;
    delete mem;
}

void Game::run() {
    while (!_quit) {
        print();
        UI::instance()->queryCommand(*this);
    }
}

void Game::step() {
    player->step();
    level->stepObjects();
}

void Game::print() {
    UI& ui = *UI::instance();
    if (gnarly) {
        // Don't compute FOV in basic mode.
        level->computeFOV(player->getY(), player->getX(), 20);
    }
    display.draw(ui);
    level->draw(*mem);
    ui.cursor(player->getY(), player->getX());
    ui.redraw();
}

class Game::MoveIntoVisitor : public LevelObjectVisitor {
    Game& game;
    Direction d;
public:
    bool keepMoving;

    MoveIntoVisitor(Game& g, Direction d) : game(g), d(d), keepMoving(true) { }
    void visit(Staircase& s) {
        game.makeNewLevel();
        keepMoving = false;
    }
    void visit(Character& c) {
        if (gnarly && c.isEnemy(Team::instance(Team::Players))) {
            game.attack(d);
            keepMoving = false;
        }
    }
    void visit(Gold& g) {
        if (g.canPickUp()) {
            g.use(game.player);
            ostringstream line;
            line << g.amount() << " gold.";
            UI::instance()->say(line.str());
            delete &g;
            // Then move onto the gold tile, so leave `keepMoving = true`.
        }
    }
};

void Game::move(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();

    LevelObject* obj = level->objectAt(ny, nx);

    if (obj) {
        // Walked into an object. What to do?
        MoveIntoVisitor visitor(*this, d);
        obj->accept(visitor);
        if (!visitor.keepMoving) {
            // Something happened, so don't do anything more.
            return;
        }
    }

    if (player->moveRelative(d)) {
        // A player action happened, so step.
        step();
    } else {
        UI::instance()->say("You can't pass that way.");
    }
}

void Game::attack(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();
    if (level->free(ny, nx)) {
        UI::instance()->say("You swing at open space.");
        return;
    }
    // XXX ?
    Character* target = dynamic_cast<Character*>(level->objectAt(ny, nx));
    if (target) {
        player->attack(target);
        step();
    } else {
        UI::instance()->say("You can't attack that.");
    }
}

void Game::use(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();
    // XXX these messages are wrong
    if (level->free(ny, nx)) {
        UI::instance()->say("You drink an imaginary potion.");
        return;
    }
    ItemAdapter* target = dynamic_cast<ItemAdapter*>(level->objectAt(ny, nx));
    if (target) {
        if (player->addToInventory(target)) {
            step();
        }
    } else {
        UI::instance()->say("That doesn't appear to be drinkable.");
    }
}

void Game::skill(int i) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    if (player->useSkill(i)) {
        step();
    } else {
        UI::instance()->say(" Skill failed.");
    }
}

void Game::wait() {
    step();
}

void Game::restart() {
    Potion::resetUsed();
    _shouldRestart = true;
    _quit = true;
}

void Game::quit() {
    _quit = true;
}

void Game::inventory() {
    if (gnarly) {
        player->viewInventory();
    }
}

void Game::confirm() {
}

LevelObject* Game::getTarget(int range) {
    // Get a position using target, and return the object at that location
    pair<int,int> tar = Target::getTarget(player->getY(), player->getX(), range);
    if (Target::validTarget(tar)) {
        print();
        return level->objectAt(tar.first, tar.second);
    } else {
        print();
        return 0;
    }
}

void Game::notifyPlayerDeath() {
    if (gameOver) return;
    gameOver = true;
    // Update the game screen (including messages) before showing the popup.
    print();
    if (gnarly) {
        PopUpCreator::defeat(player->score());
    } else {
        ostringstream line;
        line << "You Lose, game over. Score: " << player->score() << ". Restart or quit.";
        UI::instance()->say(line.str());
    }
}

void Game::makeNewLevel() {
    // Don't bother if the game is already over.
    if (gameOver) return;
    // Did we hit the end of the dungeon?
    if (dlvl >= (signed)plan.levels.size()) {
        gameOver = true;
        print();
        if (gnarly) {
            PopUpCreator::victory(player->score());
        } else {
            ostringstream line;
            line << "You win! Score: " << player->score() << ". Restart or quit.";
            UI::instance()->say(line.str());
        }
        return;
    }
    // Remove the old level, if necessary.
    if (level) {
        UI::instance()->say("You descended a level.");
        level->remove(player);
        delete level;
    }
    if (mem) {
        delete mem;
    }
    dlvl++;
    level = plan.levels[dlvl - 1]->generateLevel(player, dlvl);
    mem = new Memory(level->height(), level->width());
    display.add(mem, 0);
    display.add(level, 1);

    // Wear off buffs on the player.
    player->stripBuffs();

    // Show the intro message for this level.
    if (gnarly) {
        PopUpCreator::level(dlvl);
    }
}

Game* Game::instance(bool reset) {
    if (_instance == 0 || reset) {
        if (_instance != 0) {
            delete _instance;
        } else {
            atexit(cleanup);
        }
        _instance = new Game;
    }
    return _instance;
}

void Game::cleanup() {
    delete _instance;
}
