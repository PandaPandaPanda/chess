CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = Bishop.o Board.o Cell.o ChessPiece.o Color.o Computer.o Computer1.o Computer2.o Computer3.o Computer4.o Game.o Human.o King.o Knight.o main.o Pawn.o Player.o Queen.o Rook.o Team.o TextDisplay.o sdl_wrap.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL2 -lSDL2_image -lSDL2_ttf

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
