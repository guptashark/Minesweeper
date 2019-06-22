#include <stdlib.h>
#include "tile.h"
#include "board.h"

struct tile *
tile_ctor(struct board *b, int x, int y, bool has_mine) {

	struct tile *t = malloc(sizeof(struct tile));
	t->x = x;
	t->y = y;
	t->b = b;
	t->has_mine = has_mine;

	t->status = HIDDEN;
	t->num_adjacent_mines = 0;

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

char 
tile_print(struct tile *tp) {
	if(tp->status == HIDDEN) {
		return '.';
	} 

	if(tp->has_mine) {
		return '*';
	}

	if(tp->num_adjacent_mines == 0) {
		return ' ';
	} else {
		return tp->num_adjacent_mines + '0';
	}	
}

int
touch_tile(struct tile *t) {
	// No point in touching a tile already opened. 
	if(t->status == OPENED) {
		return -1;
	} 

	t->status = OPENED;

	if(t->has_mine) {
		return 1;
	}

	// unopened and has no mine. 
	// so now, check nearby tiles to see what 
	// to display
	int ret = board_get_num_adjacent_mines(t->b, t->x, t->y);
	
	t->num_adjacent_mines = ret;

	if(t->num_adjacent_mines == 0) {
		board_touch_adjacent_tiles(t->b, t->x, t->y);
	}
	return 0;

}
