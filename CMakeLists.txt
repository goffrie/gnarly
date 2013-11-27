cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    displayable.cpp
    levelobject/monster/dragon.cpp
    levelobject/monster/merchant.cpp
    levelobject/monster/monster.cpp
    levelobject/player/dwarfplayer.cpp
    levelobject/player/humanplayer.cpp
    levelobject/player/orcplayer.cpp
    levelobject/player/elfplayer.cpp
    levelobject/player/player.cpp
    levelobject/related/basicbuff.cpp
    levelobject/related/skills/divinemight.cpp
    levelobject/related/skills/doublestrike.cpp
    levelobject/related/skills/fireball.cpp
    levelobject/related/skills/heal.cpp
    levelobject/related/skills/mindcontrol.cpp
    levelobject/related/skills/skill.cpp
    levelobject/related/skills/stealth.cpp
    levelobject/related/attributedecorator.cpp
    levelobject/related/classbuff.cpp
    levelobject/related/attributes.cpp
    levelobject/related/class.cpp
    levelobject/related/paladin.cpp
    levelobject/related/thief.cpp
    levelobject/related/wizard.cpp
    levelobject/staircase.cpp
    levelobject/character.cpp
    levelobject/gold.cpp
    levelobject/levelobject.cpp
    levelobject/potion.cpp
    levelobject/dragongold.cpp
    levelobjectvisitor.cpp
    shadowcasting/intervalset.cpp
    shadowcasting/shadowcast.cpp
    levelgen/bspgen.cpp
    levelgen/levelgen.cpp
    levelgen/aggregationgen.cpp
    levelgen/forestgen.cpp
    display.cpp
    dungeon.cpp
    memory.cpp
    surface.cpp
    target.cpp
    basicui.cpp
    ui.cpp
    basicspawn.cpp
    commandargs.cpp
    team.cpp
    direction.cpp
    util.cpp
    main.cpp
    playerselect.cpp
    level.cpp
    cursesui.cpp
    game.cpp
    playerstatus.cpp
    popup/popup.cpp
)

include_directories(gnarly . levelobject levelobject/player levelobject/related levelobject/monster levelobject/related/skills popup)
add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
