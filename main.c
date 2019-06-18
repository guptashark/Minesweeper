#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tile {

	bool has_mine;
	int x;
	int y;

	// the adjacent tiles
	//struct tile adjacent[8];

	int num_adjacent_mines;

};

struct tile *
tile_ctor(int x, int y, bool has_mine) {

	struct tile *ret = malloc(sizeof(struct tile));
	ret->x = x;
	ret->y = y;
	ret->has_mine = has_mine;

	return ret;
}

char tile_print(struct tile *tp) {

	if(tp->has_mine) {
		return 'X';
	} else {
		return 'O';
	}
}

struct board {
	int rows;
	int cols;

	struct tile **tiles;
};

void board_init(struct board *bp, int rows, int cols, int mine_factor) {

	bp->rows = rows;
	bp->cols = cols;

	bp->tiles = malloc(sizeof(struct tile *) * rows * cols);

	for(int i =0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			bp->tiles[i * bp->cols + j] = tile_ctor(i, j, true);
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

int main(void) {

	printf("Welcome to Minesweeper!\n\n");

	struct board b;
	board_init(&b, 5, 6, 3);

	board_print(&b);

}
