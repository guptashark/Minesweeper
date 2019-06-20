#include "game.h"

int
game_init(struct game *g) {

	board_init(&(g->b), 10, 10, 20);
	g->bp = &(g->b);
	return 0;
}

int
game_dbstart(struct game *g) {
	board_dbprint(g->bp);
	return 0;
}

