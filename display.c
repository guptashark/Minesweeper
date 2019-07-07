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
}

int display_print(struct display *d) {
	(void)d;
	return 0;
}

