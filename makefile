CC = gcc
LIB = -lncurses
INC = -Iinclude

game: 
	$(CC) -o $@ src/*.c $(LIB) $(INC)

clean:
	rm game