CXX      := g++
CXXFLAGS := -Wall -g -MMD
TARGET1  := Chess
TARGET2  := Bonus
OBJS     := ChessBoard.o ChessPiece.o Pawn.o Rook.o Bishop.o Knight.o Queen.o King.o

$(TARGET1): ChessMain.o $(OBJS)
	$(CXX) ChessMain.o $(OBJS) -o $(TARGET1)

$(TARGET2): LaskerThomas.o $(OBJS)
	$(CXX) LaskerThomas.o $(OBJS) -o $(TARGET2)

-include $(OBJS:.o=.d)

clean:
	rm -rf *.o *.d $(TARGET1) $(TARGET2)


