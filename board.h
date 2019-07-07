
#include <stdio.h>
#include <stdbool.h>

#include "tile.h"
#include "display.h"

struct board {

	int rows;
	int cols;

	// A pointer to some kind of display obj
	// losing type safety here. 
	struct display *dsp;

	struct tile ***tiles;

	int num_mines;
	int cleared_tiles;
};

/* Not entirely robust, in the case of bad num_mines */
int 
board_init(struct board *b, int rows, int cols, int num_mines);

int 
board_init_specified_state
(struct board *b, int rows, int cols, int num_mines, int state);

int
board_set_display
(struct board *b, struct display *dsp);

int 
board_init_from_file(struct board *b, int rows, int cols, FILE *spec);

int 
board_dbprint(struct board *b);

int
board_print(struct board *b);

int 
board_get_num_adjacent_mines(struct board * b, int x, int y);

int
board_touch_tile(struct board *b, int x, int y);

int
board_touch_adjacent_tiles(struct board *b, int x, int y);
