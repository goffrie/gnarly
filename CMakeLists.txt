cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    basicui.cpp
    cursesui.cpp
    display.cpp
    displayable.cpp
    dungeon.cpp
    dungeongen/bspgen.cpp
    game.cpp
    level.cpp
    levelobject/character.cpp
    levelobject/dragongold.cpp
    levelobject/gold.cpp
    levelobject/levelobject.cpp
    levelobject/monster/dragon.cpp
    levelobject/monster/merchant.cpp
    levelobject/monster/monster.cpp
    levelobject/player/dwarfplayer.cpp
    levelobject/player/elfplayer.cpp
    levelobject/player/humanplayer.cpp
    levelobject/player/orcplayer.cpp
    levelobject/player/player.cpp
    levelobject/potion.cpp
    levelobject/related/attributedecorator.cpp
    levelobject/related/attributes.cpp
    levelobject/related/potionbuff.cpp
    levelobject/staircase.cpp
    levelobjectvisitor.cpp
    main.cpp
    playerstatus.cpp
    popup.cpp
    shadowcasting/intervalset.cpp
    team.cpp
    ui.cpp
)

include_directories(gnarly . levelobject levelobject/player levelobject/related levelobject/monster)
add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
