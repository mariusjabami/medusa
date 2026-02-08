#include <stdio.h>
#include "../includes/parser.h"

void print_f(int len, int num, char (*text)[len]){
	for (int i = 0; i < num; i++) {
	
		printf("%s", text[i]);
	}
}

int read_file(char *file, char (*text)[100]){

	int i = 0;

	FILE *f = fopen(file, "r");

	if (!f) return -1;

	while (i < 100 && fgets(*(text + i), 100, f) != NULL) {
		i++;
	}

	fclose(f);
	return i;
}


