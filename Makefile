CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11 -I. -Ilevelobject -Ilevelobject/related -Ilevelobject/player -Ilevelobject/monster -Idungeongen
LDFLAGS=-lncurses
EXEC=gnarly
OBJECTS=\
	levelobject/related/attributes.o \
	levelobject/related/attributedecorator.o \
	levelobject/related/potionbuff.o \
	levelobject/player/player.o \
	levelobject/player/humanplayer.o \
	levelobject/player/dwarfplayer.o \
	levelobject/player/elfplayer.o \
	levelobject/player/orcplayer.o \
	levelobject/monster/monster.o \
	levelobject/monster/merchant.o \
	levelobject/monster/dragon.o \
	levelobject/levelobject.o \
	levelobject/character.o \
	levelobject/potion.o \
	levelobject/gold.o \
	levelobject/dragongold.o \
	levelobject/staircase.o \
	dungeongen/dungeongen.o \
	dungeongen/bspgen.o \
	dungeongen/aggregationgen.o \
	ui.o \
	basicui.o \
	cursesui.o \
	levelobjectvisitor.o \
	game.o \
	dungeon.o \
	display.o \
	displayable.o \
	playerstatus.o \
	level.o \
	main.o \
	team.o \
	popup.o \
	commandargs.o \
	direction.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
