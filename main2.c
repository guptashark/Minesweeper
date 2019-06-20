#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"

int main(void) {

	struct game g;
	struct game *gp = &g;

	game_init(gp, stdin);
	game_dbstart(gp);

	return 0;
}
