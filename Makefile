CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 

all: 
	$(CC) $(CFLAGS) display.c tile.c board.c game.c main.c -lcurses
	./a.out default_5x5.txt

	
