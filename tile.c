#include <stdlib.h>
#include "tile.h"

struct tile *
tile_ctor(struct board *b, int x, int y, bool has_mine) {

	struct tile *t = malloc(sizeof(struct tile));
	t->x = x;
	t->y = y;
	t->b = b;
	t->has_mine = has_mine;

	t->status = 0;
	return t;
}

char 
tile_dbprint(struct tile *tp) {
	if(tp->has_mine) {
		return 'X';
	} else {
		return 'O';
	}
}
