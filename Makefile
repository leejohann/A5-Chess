CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = chess
OBJECTS = main.o posn.o board.o piece.o tile.o subject.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
