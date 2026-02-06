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

	for (int i = 0; i < num_of_dir; i++) {

		char fullpath[256];


		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirs[i]);
		
		printf(" \nINIT FILE: %s\n", dirs[i]);

		int ptr = read_file(fullpath, text);
		if(ptr <= 0) continue;
		
		print_f(100, ptr, text);

		printf(" \nEND FILE: %s\n", dirs[i]);


	}

	free(text);
	free(dirs);

}
