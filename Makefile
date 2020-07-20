# Make file

# Compiler
CC := g++

# objects
OBJ_LIST = board.o

build : $(OBJ_LIST)
	$(CC) $(OBJ_LIST) 

board_c : board.c board.h
	$(CC) $(FLAGS) board.c -o board.h

.PYONY clean:
	rm -f *.o *.out