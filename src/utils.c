#include <stdio.h>
#include <stdlib.h>
#include "../includes/scanner.h"
#include "../includes/parser.h"

int str_equals(const char *a, const char *b){
	while (*a && *b) {

		if(*a != *b) return 0;

		a++;
		b++;
	}

	return *a == *b;
}

void run(char *path){

	int num_of_dir = 0;

	char (*text)[100] = malloc(100 * sizeof *text);
	char (*dirs)[100] = malloc(100 * sizeof *text);

	read_dir(path, &num_of_dir, dirs);

	FILE *out = fopen("out.txt", "w");
	if (!out) {
	
		perror("out.txt");
		return;
	}

	for (int i = 0; i < num_of_dir; i++) {

		char fullpath[256];

		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirs[i]);
		
		int ptr = read_file(fullpath, text);
		if(ptr <= 0) continue;
		
		for (int j = 0; j < ptr; j++) {

			fprintf(out, "%s", text[j]);
		
		}

	}
	fclose(out);

	free(text);
	free(dirs);
}
