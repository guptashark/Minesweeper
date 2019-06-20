#include "board.h"

struct game {
	struct board b;
	struct board *bp;

};

int
game_init(struct game *g);


int
game_dbstart(struct game *g);

