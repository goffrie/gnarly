cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    displayable.cpp
    ui.cpp
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
    levelobject/related/attributes.cpp
    levelobject/related/class.cpp
    levelobject/related/classbuff.cpp
    levelobject/related/paladin.cpp
    levelobject/related/thief.cpp
    levelobject/related/wizard.cpp
    levelobject/staircase.cpp
    levelobject/dragongold.cpp
    levelobject/gold.cpp
    levelobject/levelobject.cpp
    levelobject/potion.cpp
    levelobject/character.cpp
    levelobjectvisitor.cpp
    shadowcasting/intervalset.cpp
    shadowcasting/shadowcast.cpp
    dungeongen/bspgen.cpp
    dungeongen/dungeongen.cpp
    dungeongen/aggregationgen.cpp
    main.cpp
    commandargs.cpp
    direction.cpp
    display.cpp
    dungeon.cpp
    memory.cpp
    surface.cpp
    target.cpp
    team.cpp
    level.cpp
    basicui.cpp
    game.cpp
    playerstatus.cpp
    cursesui.cpp
    playerselect.cpp
    popup.cpp
    util.cpp
)

include_directories(gnarly . levelobject levelobject/player levelobject/related levelobject/monster levelobject/related/skills)
add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
