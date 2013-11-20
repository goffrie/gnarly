cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    attributedecorator.cpp
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
    potion.cpp
    potionbuff.cpp
    ui.cpp
)

add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
