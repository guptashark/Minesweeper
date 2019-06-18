#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tile {

	bool cleared;
	
	bool has_mine;
	int x;
	int y;

	// the adjacent tiles
	//struct tile adjacent[8];

	int num_adjacent_mines;
	struct tile *adjacents[4];

};

struct tile *
tile_ctor(int x, int y, bool has_mine) {

	struct tile *ret = malloc(sizeof(struct tile));
	ret->x = x;
	ret->y = y;
	ret->has_mine = has_mine;
	ret->cleared = false;

	// This is default initialized to 0
	ret->num_adjacent_mines = 0;
	for(int i =0; i < 4; i++) {
		ret->adjacents[i] = NULL;
	}

	return ret;
}

char tile_print(struct tile *tp) {

	if(tp->cleared) {
		if(tp->has_mine) {
			return 'X';
		} else {
			if(tp->num_adjacent_mines > 0) {
				return '0' + tp->num_adjacent_mines;
			} else {
				return ' ';
			}
		}
	} else {
		return '%';
	}	
}

struct board {
	int rows;
	int cols;

	struct tile **tiles;
};


// Hackyish. Relies on there being not too many mines, otherwise 
// random number gen may never finish. 
void board_init(struct board *bp, int rows, int cols, int num_mines) {

	(void)num_mines;


	// need to pick num_mines consecutive integers out of 
	// rows * cols. if spot already has a mine, place mine on 
	// the next spot. 

	bool *mine_spots = malloc(sizeof(bool) * rows * cols);
	for(int i = 0; i < (rows * cols); i++) {
		mine_spots[i] = false;
	}

	srand(time(NULL));
	int set_mines = 0;
	while(set_mines < num_mines) { 
		int r = rand() % (rows * cols);
		if( ! mine_spots[r]) {
			mine_spots[r] = true;
			set_mines++;
		}
	}


	bp->rows = rows;
	bp->cols = cols;

	bp->tiles = malloc(sizeof(struct tile *) * rows * cols);

	for(int i =0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			bool mine_status = mine_spots[i * bp->cols + j];
			bp->tiles[i * bp->cols + j] = tile_ctor(i, j, mine_status);
		}
	}
}

void board_print(struct board *bp) {

	for(int i =0; i < bp->rows; i++) {
		for(int j = 0; j < bp->cols; j++) {
			printf("%c", tile_print(bp->tiles[i * bp->cols + j]));
		}

		printf("\n");
	}
			
}

struct game {
	// some fail conditions and whatever. 
	int status; 	// dead, etc. 
	
	int turn;

};

int main(void) {

	printf("Welcome to Minesweeper!\n\n");

	struct board b;
	board_init(&b, 5, 6, 3);

	board_print(&b);


	



}
