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

	int num_of_dir;

	char (*text)[100] = malloc(sizeof(char[100][100]));
	char (*dirs)[100] = malloc(sizeof(char[100][100]));

	read_dir(path, &num_of_dir, dirs);

	for (int i = 0; i < num_of_dir; i++) {


		printf(" \nINIT FILE: %s\n", dirs[i]);

		int ptr = read_file(dirs[i], text);
		if(ptr <= 0) continue;
		
		print_f(100, ptr, text);

		printf(" \nEND FILE: %s\n", dirs[i]);


	}

	free(text);
	free(dirs);

}
