#include <stdlib.h>

#include "display.h"

int display_init(struct display *d, int rows, int cols, FILE *output) {

	d->rows = rows;
	d->cols = cols;
	d->output = output;
		
	d->tiles = malloc(sizeof(char) * rows * cols);

	for(int i = 0; i < d->rows; i++) {
		for(int j = 0; j < d->cols; j++) {

			d->tiles[i * d->cols + j] = '\0';
		}
	}

	return 0;
}

int display_print(struct display *d) {

	for(int i = 0; i < d->cols + 2; i++) {
		printf("-");		
	}	
	printf("\n");

	for(int i = 0; i < d->rows; i++) {
		printf("|");
		for(int j = 0; j < d->cols; j++) {
//			printf("%c", tile_print(b->tiles[i][j]));
// TODO The right printing action
			printf("X");
		}
		printf("|\n");
	}
	
	for(int i = 0; i < d->cols + 2; i++) {
		printf("-");
	}

	printf("\n");

	return 0;
}
