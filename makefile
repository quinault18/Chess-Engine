CC = g++
CFLAGS = -Wall 

INCLUDE = ./include
SRC = ./src
LIB = .
BIN = ./bin


main: libchess.a main.o board.o
	$(CC) $(CFLAGS) -o main main.o board.o -L$(LIB) -lchess
	make move


libchess.a: square.o piece.o 
	ar -rcs libchess.a square.o piece.o 

main.o: main.cpp $(INCLUDE)/board.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -c main.cpp 

board.o: $(SRC)/board.cpp $(INCLUDE)/board.h 
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/board.cpp 

square.o: $(SRC)/square.cpp $(INCLUDE)/square.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/square.cpp 

piece.o: $(SRC)/piece.cpp $(INCLUDE)/piece.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/piece.cpp 

run: main 
	./$(BIN)/main

move: *.o *.a main
	mv *.o $(BIN)
	mv *.a $(BIN)
	mv main $(BIN)

clean:
	rm -f *.a *.o main
	rm -f $(BIN)/*.a $(BIN)/*.o $(BIN)/main