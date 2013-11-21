CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11
LDFLAGS=
EXEC=shadowcast_test
OBJECTS=shadowcast_test.o intervalset.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
