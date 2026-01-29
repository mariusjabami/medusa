#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "../includes/scanner.h"
#include "../includes/parser.h"
#include "../includes/utils.h"

int main(int argc, char **argv){

	// ARRANJAR UMA MANEIRA DE LEMBRAR A ULTIMA POSICAO DO ARRAY
	//
	if (argc < 2) {
	
		printf("Uso: ./program <comando>\n");
		return 1;
	}

	if (str_equals(argv[1], "run")) {
		run(argv[2]);
	}

	return 0;
}
