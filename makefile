CC = gcc
Lib = -lncurses

game: 
	$(CC) -o $@ src/*.c $(Lib)
	