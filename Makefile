CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11
LDFLAGS=-lncurses
EXEC=gnarly
OBJECTS=\
	character.o \
	cursesui.o \
	display.o \
	displayable.o \
	dungeon.o \
	game.o \
	humanplayer.o \
	level.o \
	levelobject.o \
	levelobjectvisitor.o \
	main.o \
	player.o \
	playerstatus.o \
	basicui.o \
	attributes.o \
	monster.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
