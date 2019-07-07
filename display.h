
#include <stdio.h>

struct display {
	

	int rows;
	int cols;
	FILE *output; 
	// sockets? 	

	char *tiles;
	
		

};

int display_init(struct display *d, int rows, int cols, FILE *output);

int display_print(struct display *d);

