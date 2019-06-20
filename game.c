#include "game.h"

int
game_init(struct game *g, FILE *input) {

	g->input = input;

	// get the rows, cols and num mines
	int rows = 0;
	int cols = 0;
	int num_mines = 0;

	if(input == stdin) {
		printf("number of rows: ");
		scanf("%d", &rows);

		printf("number of cols: ");
		scanf("%d", &cols);

		printf("number of mines: ");
		scanf("%d", &num_mines);
	} else {
		fscanf(input, "%d %d %d", &rows, &cols, &num_mines);
	}
	

	board_init(&(g->b), rows, cols, num_mines);
	g->bp = &(g->b);
	return 0;
}

int
game_dbstart(struct game *g) {
	board_dbprint(g->bp);
	return 0;
}

int 
game_turn(struct game *g) {
	(void)g;
	return 0;	
}

