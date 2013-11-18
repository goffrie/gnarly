cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
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
    main.cpp
    player.cpp
    playerstatus.cpp
)
set(grapher_HEADERS
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
    player.h
    playerstatus.h
    ui.h
    util.h
)

add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
