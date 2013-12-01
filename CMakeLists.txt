cmake_minimum_required(VERSION 2.8)

project(gnarly)

find_package(Curses REQUIRED)

set(gnarly_SOURCES
    basicui.cpp
    commandargs.cpp
    cursesui.cpp
    direction.cpp
    display.cpp
    displayable.cpp
    dungeon.cpp
    game.cpp
    item/potion.cpp
    level.cpp
    levelgen/aggregationgen.cpp
    levelgen/basicspawn.cpp
    levelgen/filegen.cpp
    levelgen/finalgen.cpp
    levelgen/forestgen.cpp
    levelgen/gnarlyspawn.cpp
    levelgen/levelgen.cpp
    levelgen/levelplan.cpp
    levelgen/roomsgen.cpp
    levelobject/character.cpp
    levelobject/damage.cpp
    levelobject/dragongold.cpp
    levelobject/gold.cpp
    levelobject/itemadapter.cpp
    levelobject/levelobject.cpp
    levelobject/monster/altar.cpp
    levelobject/monster/dragon.cpp
    levelobject/monster/merchant.cpp
    levelobject/monster/monster.cpp
    levelobject/player/dwarfplayer.cpp
    levelobject/player/elfplayer.cpp
    levelobject/player/halflingplayer.cpp
    levelobject/player/humanplayer.cpp
    levelobject/player/orcplayer.cpp
    levelobject/player/player.cpp
    levelobject/related/attributedecorator.cpp
    levelobject/related/attributes.cpp
    levelobject/related/basicbuff.cpp
    levelobject/related/class.cpp
    levelobject/related/classbuff.cpp
    levelobject/related/inventory.cpp
    levelobject/related/paladin.cpp
    levelobject/related/skills/divinemight.cpp
    levelobject/related/skills/fireball.cpp
    levelobject/related/skills/heal.cpp
    levelobject/related/skills/mindcontrol.cpp
    levelobject/related/skills/skill.cpp
    levelobject/related/skills/stealth.cpp
    levelobject/related/skills/triplestrike.cpp
    levelobject/related/thief.cpp
    levelobject/related/wizard.cpp
    levelobject/staircase.cpp
    levelobjectvisitor.cpp
    main.cpp
    memory.cpp
    object.cpp
    playerselect.cpp
    playerstatus.cpp
    popup/inventorypopup.cpp
    popup/popup.cpp
    popup/popupcreator.cpp
    rand.cpp
    shadowcasting/intervalset.cpp
    shadowcasting/shadowcast.cpp
    surface.cpp
    target.cpp
    team.cpp
    ui.cpp
    util.cpp
)

include_directories(gnarly . levelobject levelobject/player levelobject/related levelobject/monster levelobject/related/skills popup item)
add_executable(gnarly ${gnarly_SOURCES})
target_link_libraries(gnarly ${CURSES_LIBRARIES})
