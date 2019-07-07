#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <stdbool.h>

#include "game.h"

int main(int argc, char *argv[]) {

	struct game g;
	struct game *gp = &g;
	// this implies there is a file to read from. 

	FILE *input = NULL;
	if(argc == 2) {
		input = fopen(argv[1], "r");
	} else {
		input = stdin;
	}
/*
	// initialize ncurses
	initscr();
	mvaddch(0, 0, 'h');
	mvaddch(0, 1, 'b');
	mvaddch(1, 0, 'c');
	getch();
	endwin();		
	printf("\n\n\n");
*/	
	
	struct display d;
	display_init(&d, 5, 5, NULL);

	game_init(gp, input);
	board_set_display(gp->bp, &d);
	while(true) {
		int ret = game_turn(gp);
		if(ret == 1) {
			printf("You touched a mine! Game over!\n");
			return 0;
		} else if(ret == 2) {
			printf("You cleard all the mines! You win!\n");
			return 0;
		}
	}

	return 0;
}
