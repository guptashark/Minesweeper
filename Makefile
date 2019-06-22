CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 

all: 
	$(CC) $(CFLAGS) tile.c board.c game.c main.c 
	./a.out default_10x10.txt

	
