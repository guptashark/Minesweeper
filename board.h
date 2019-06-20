#include <stdio.h>
#include <stdbool.h>

#include "tile.h"

struct board {

	int rows;
	int cols;
	struct tile ***tiles;

	int num_mines;
};

/* Not entirely robust, in the case of bad num_mines */
int 
board_init(struct board *b, int rows, int cols, int num_mines);

int 
board_init_specified_state
(struct board *b, int rows, int cols, int num_mines, int state);

int 
board_init_from_file(struct board *b, int rows, int cols, FILE *spec);

int 
board_dbprint(struct board *b);
