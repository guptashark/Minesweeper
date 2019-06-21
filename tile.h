#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

struct board;

enum tile_status {HIDDEN, OPENED};

struct tile {
	
	struct board *b;
		
	int x;
	int y;

	bool has_mine;
	enum tile_status status;
	int num_adjacent_mines;

	
};


struct tile *
tile_ctor(struct board *b, int x, int y, bool has_mine);

char 
tile_dbprint(struct tile *tp);

char 
tile_print(struct tile *tp);


int
touch_tile(struct tile *t);

#endif
