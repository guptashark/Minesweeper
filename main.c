#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

	game_init(gp, input);
	while(true) {
		int ret = game_turn(gp);
		if(ret == 1) {
			printf("You touched a mine! Game over!\n");
		}
	}

	return 0;
}
