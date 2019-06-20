#include <stdio.h>

#include "board.h"

struct game {

	// These are the boards
	struct board b;
	struct board *bp;

	// where we get game inputs. 
	FILE *input;
};

int
game_init(struct game *g, FILE *input);


int
game_dbstart(struct game *g);

int
game_turn(struct game *g);

