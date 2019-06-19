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
	// struct tile adjacent[8];

	int num_adjacent_mines;

	int num_adjacent;
	struct tile *adjacents[8];

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
	for(int i =0; i < 8; i++) {
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

int touch_single_tile(struct tile *tp) {

	tp->cleared = true;
	if(tp->has_mine) {
		return 1;
	} else {
		return 0;
	}
}

int touch_tile(struct tile *tp) {
	if(tp == NULL) {
		return 0;
	}
	
	if(tp->has_mine) {
		return 1;
	}
	
	for(int i = 0; i < tp->num_adjacent; i++) {
		if(tp->adjacents[i]->has_mine) {
			tp->num_adjacent_mines++;
		}
	}

	tp->cleared = true;
	if(tp->num_adjacent_mines == 0) {
		for(int i = 0; i < tp->num_adjacent; i++) {
			touch_tile(tp->adjacents[i]);
		}
	}
	return 0;
}

int tile_set_adjacent(struct tile *tp, struct tile *adj) {
	tp->adjacents[tp->num_adjacent] = adj;
	tp->num_adjacent++;

	return 0;
}

struct board {
	int rows;
	int cols;

	struct tile **tiles;
};



void board_set_tile_adjacents(struct board *bp) {
	
	// center tiles - 
	int r = bp->cols;
	for(int i = 1; i < (bp->rows - 1); i++) {
		for(int j = 1; j < (bp->cols - 1); j++) {
			int k = i * bp->cols + j;
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i-1) * r + j]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i-1) * r + j + 1]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[i * r + j + 1]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i+1) * r + j + 1]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i+1) * r + j]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i+1) * r + j - 1]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[i * r + j - 1]);
			tile_set_adjacent(bp->tiles[k], bp->tiles[(i+1) * r + j - 1]);
		}
	}

	// top edge - excluding corners; 
	for(int j = 1; j < (bp->cols - 1); j++) {
		tile_set_adjacent(bp->tiles[j], bp->tiles[j-1]);
		tile_set_adjacent(bp->tiles[j], bp->tiles[j+1]);
		tile_set_adjacent(bp->tiles[j], bp->tiles[bp->cols + j - 1]);
		tile_set_adjacent(bp->tiles[j], bp->tiles[bp->cols + j ]);
		tile_set_adjacent(bp->tiles[j], bp->tiles[bp->cols + j + 1]);
	}

	// bottom edge - excluding corners; 
	int bl = bp->cols * (bp->rows - 1);
	for(int j = 1; j < (bp->cols - 1); j++) {
		tile_set_adjacent(bp->tiles[bl + j], bp->tiles[bl + j-1]);
		tile_set_adjacent(bp->tiles[bl + j], bp->tiles[bl + j+1]);
		tile_set_adjacent(bp->tiles[bl + j], bp->tiles[bl - r + j - 1]);
		tile_set_adjacent(bp->tiles[bl + j], bp->tiles[bl - r + j ]);
		tile_set_adjacent(bp->tiles[bl + j], bp->tiles[bl - r + j + 1]);
	}

	// left edge - excluding corners;
	for(int i = 1; i < (bp->rows - 1); i++) {
		tile_set_adjacent(bp->tiles[i * r], bp->tiles[(i - 1) * r]);
		tile_set_adjacent(bp->tiles[i * r], bp->tiles[(i + 1) * r]);
		tile_set_adjacent(bp->tiles[i * r], bp->tiles[(i - 1) * r + 1]);
		tile_set_adjacent(bp->tiles[i * r], bp->tiles[i * r + 1]);
		tile_set_adjacent(bp->tiles[i * r], bp->tiles[(i + 1) * r + 1]);
	}

	// right edge - excluding corners;

	int tr = bp->cols - 1;
	for	(int i = 1; i < (bp->rows - 1); i++) {
		tile_set_adjacent(bp->tiles[i * r + tr], bp->tiles[(i-1) * r + tr]);
		tile_set_adjacent(bp->tiles[i * r + tr], bp->tiles[(i+1) * r + tr]);
		tile_set_adjacent(bp->tiles[i * r + tr], bp->tiles[i * r + tr -1]);
		tile_set_adjacent(bp->tiles[i * r + tr], bp->tiles[(i-1) * r + tr - 1]);
		tile_set_adjacent(bp->tiles[i * r + tr], bp->tiles[(i+1) * r + tr - 1]);
	}
}


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

	board_set_tile_adjacents(bp);
}

void board_print(struct board *bp) {

	for(int i = 0; i < (bp->cols + 2); i++) {
		printf("-");
	}

	printf("\n");

	for(int i =0; i < bp->rows; i++) {
		printf("|");
		for(int j = 0; j < bp->cols; j++) {
			printf("%c", tile_print(bp->tiles[i * bp->cols + j]));
		}

		printf("|\n");
	}

	for(int i = 0; i < (bp->cols + 2); i++) {
		printf("-");
	}

	printf("\n");
}

struct game {
	// some fail conditions 
	int status; 	// dead, etc. 
	
	int turn;

};

int main(void) {

	printf("Welcome to Minesweeper!\n\n");

	struct board b;
	board_init(&b, 10, 10, 10);

	board_print(&b);

	while(true) {
		int x; 
		int y;
		scanf("%d", &x);
		scanf("%d", &y);

		printf("You picked: %d, %d\n", x, y);
		
		touch_tile(b.tiles[x * b.cols + y]);
		board_print(&b);
	}

	board_print(&b);

}

