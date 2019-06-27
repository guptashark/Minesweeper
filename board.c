#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "board.h"

/* Not entirely robust, in the case of bad num_mines */
int 
board_init(struct board *b, int rows, int cols, int num_mines) {
	b->rows = rows;
	b->cols = cols;
	
	b->tiles = malloc(sizeof(struct tile **) * rows);
	for(int i = 0; i < rows; i++) {
		b->tiles[i] = malloc(sizeof(struct tile *) * cols);
	}

	srand(time(NULL));
	int num_set_mines = 0;
	bool *mine_spots = malloc(sizeof(bool) * rows * cols);
	for(int i = 0; i < (rows * cols); i++) mine_spots[i] = false;

	while(num_set_mines < num_mines) {
		int spot = rand() % (rows * cols);
		if(mine_spots[spot] == false) {
			mine_spots[spot] = true;
			num_set_mines++;
		}
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			b->tiles[j][i] = tile_ctor(b, i, j, mine_spots[i * cols + j]);
		}
	}
	return 0;
}

int 
board_init_specified_state
(struct board *b, int rows, int cols, int num_mines, int state) {
	(void)b;
	(void)rows;
	(void)cols;
	(void)num_mines;
	(void)state;
	return 0;
}

int 
board_init_from_file(struct board *b, int rows, int cols, FILE *spec) {
	(void)b;
	(void)rows;
	(void)cols;
	(void)spec;
	return 0;
}

int 
board_dbprint(struct board *b) {

	for(int i = 0; i < b->cols + 2; i++) {
		printf("-");		
	}	
	printf("\n");

	for(int i = 0; i < b->rows; i++) {
		printf("|");
		for(int j = 0; j < b->cols; j++) {
			printf("%c", tile_dbprint(b->tiles[i][j]));
		}
		printf("|\n");
	}
	
	for(int i = 0; i < b->cols + 2; i++) {
		printf("-");
	}

	printf("\n");

	return 0;
}

int 
board_print(struct board *b) {

	for(int i = 0; i < b->cols + 2; i++) {
		printf("-");		
	}	
	printf("\n");

	for(int i = 0; i < b->rows; i++) {
		printf("|");
		for(int j = 0; j < b->cols; j++) {
			printf("%c", tile_print(b->tiles[i][j]));
		}
		printf("|\n");
	}
	
	for(int i = 0; i < b->cols + 2; i++) {
		printf("-");
	}

	printf("\n");

	return 0;
}

int
board_touch_tile(struct board *b, int x, int y) {

	if(x < 0 || x >= b->cols) {
		return 1;
	}

	if(y < 0 || y >= b->rows) {
		return 1;
	}

	int ret = touch_tile(b->tiles[y][x]);
	// Rn, don't care about the -1
	if(ret == 1) {
		return 1;
	} else {
		return 0;
	}
}

int
board_touch_adjacent_tiles(struct board *b, int x, int y) {

	board_touch_tile(b, x-1, y);
	board_touch_tile(b, x+1, y);
	board_touch_tile(b, x-1, y-1);
	board_touch_tile(b, x, y-1);
	board_touch_tile(b, x+1, y-1);
	board_touch_tile(b, x-1, y+1);
	board_touch_tile(b, x, y+1);
	board_touch_tile(b, x+1, y+1);

	return 0;
}

static
int 
board_query_tile(struct board *b, int x, int y) {
	if(x < 0 || x >= b->cols) {
		return 0;
	} 

	if(y < 0 || y >= b->rows) {
		return 0;
	}

	if(b->tiles[y][x]->has_mine) {
		return 1;
	} else {
		return 0;
	}
}

int 
board_get_num_adjacent_mines(struct board *b, int x, int y) {

	int ta = 0; // total adjacent

	ta += board_query_tile(b, x-1, y-1);
	ta += board_query_tile(b, x, y-1);
	ta += board_query_tile(b, x+1, y-1);
	ta += board_query_tile(b, x-1, y);
	ta += board_query_tile(b, x+1, y);
	ta += board_query_tile(b, x-1, y+1);
	ta += board_query_tile(b, x, y+1);
	ta += board_query_tile(b, x+1, y+1);


	return ta;

}
