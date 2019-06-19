#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

struct board {

	int rows;
	int cols;
	struct tile ***tiles;

	int num_mines;
};

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
board_print(struct board *b) {

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

struct game {



};

int main(void) {

	struct board b;
	struct board *bp = &b;

	board_init(bp, 10, 10, 20);
	board_print(bp);

}
