#include <stdbool.h>

struct board;

struct tile {
	
	int x;
	int y;

	bool has_mine;

	struct board *b;

	int status;

};


struct tile *
tile_ctor(struct board *b, int x, int y, bool has_mine);

char 
tile_dbprint(struct tile *tp);
