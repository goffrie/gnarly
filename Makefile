CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11 -I. -Ilevelobject -Ilevelobject/related -Ilevelobject/player -Ilevelobject/monster
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
	levelobject/levelobject.o \
	levelobject/character.o \
	levelobject/potion.o \
	levelobject/gold.o \
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
	team.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
