CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11
LDFLAGS=-lncurses
EXEC=gnarly
OBJECTS=\
	ui.o \
	basicui.o \
	cursesui.o \
	game.o \
	dungeon.o \
	display.o \
	displayable.o \
	playerstatus.o \
	attributes.o \
	attributedecorator.o \
	level.o \
	levelobject.o \
	levelobjectvisitor.o \
	character.o \
	player.o \
	humanplayer.o \
	monster.o \
	potion.o \
	potionbuff.o \
	main.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
