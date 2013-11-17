CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11
LDFLAGS=-lncurses
EXEC=gnarly
OBJECTS=character.o cursesgrid.o display.o displayable.o dungeon.o game.o humanplayer.o main.o player.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
