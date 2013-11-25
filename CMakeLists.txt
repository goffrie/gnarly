cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    level.cpp
    direction.cpp
    commandargs.cpp
    display.cpp
    displayable.cpp
    ui.cpp
    target.cpp
    popup.cpp
    memory.cpp
    team.cpp
    levelobject/staircase.cpp
    levelobject/monster/dragon.cpp
    levelobject/monster/monster.cpp
    levelobject/monster/merchant.cpp
    levelobject/levelobject.cpp
    levelobject/potion.cpp
    levelobject/dragongold.cpp
    levelobject/gold.cpp
    levelobject/player/orcplayer.cpp
    levelobject/player/humanplayer.cpp
    levelobject/player/elfplayer.cpp
    levelobject/player/player.cpp
    levelobject/player/dwarfplayer.cpp
    levelobject/character.cpp
    levelobject/related/thief.cpp
    levelobject/related/basicbuff.cpp
    levelobject/related/class.cpp
    levelobject/related/wizard.cpp
    levelobject/related/attributedecorator.cpp
    levelobject/related/paladin.cpp
    levelobject/related/attributes.cpp
    levelobject/related/skills/stealth.cpp
    levelobject/related/skills/doublestrike.cpp
    levelobject/related/skills/mindcontrol.cpp
    levelobject/related/skills/heal.cpp
    levelobject/related/skills/divinemight.cpp
    levelobject/related/skills/skill.cpp
    levelobject/related/skills/fireball.cpp
    dungeon.cpp
    playerselect.cpp
    levelobjectvisitor.cpp
    cursesui.cpp
    dungeongen/bspgen.cpp
    dungeongen/aggregationgen.cpp
    dungeongen/dungeongen.cpp
    surface.cpp
    basicui.cpp
    main.cpp
    playerstatus.cpp
    shadowcasting/intervalset.cpp
    shadowcasting/shadowcast.cpp
    game.cpp
)

include_directories(gnarly . levelobject levelobject/player levelobject/related levelobject/monster levelobject/related/skills)
add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
