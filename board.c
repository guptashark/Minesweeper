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
	for(int i = 0; i < cols; i++) {
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
			b->tiles[i][j] = tile_ctor(b, i, j, mine_spots[i * cols + j]);
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

	for(int i = 0; i < b->rows + 2; i++) {
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
	
	for(int i = 0; i < b->rows + 2; i++) {
		printf("-");
	}

	printf("\n");

	return 0;
}


