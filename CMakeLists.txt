cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    attributes.cpp
    basicui.cpp
    character.cpp
    cursesui.cpp
    display.cpp
    displayable.cpp
    dungeon.cpp
    game.cpp
    humanplayer.cpp
    level.cpp
    levelobject.cpp
    levelobjectvisitor.cpp
    main.cpp
    monster.cpp
    player.cpp
    playerstatus.cpp
    ui.cpp
)
set(grapher_HEADERS
    attributes.h
    basicui.h
    character.h
    commandhandler.h
    cursesui.h
    display.h
    displayable.h
    dungeon.h
    game.h
    humanplayer.h
    level.h
    levelobject.h
    levelobjectvisitor.h
    monster.h
    player.h
    playerstatus.h
    randomspawn.h
    ui.h
    util.h
)

add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
