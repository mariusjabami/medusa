#include <stdio.h>
#include <dirent.h>
#include "../includes/utils.h"
#include "../includes/server.h"

int main(int argc, char **argv){

	// ARRANJAR UMA MANEIRA DE LEMBRAR A ULTIMA POSICAO DO ARRAY
	
	if (argc < 4) {
		printf("Uso: ./program run <dir> <language>\n");
		return 1;
	}

	if (str_equals(argv[1], "run")) {

		run(argv[2]);
		analyze_with_medusa("out.txt", "relatorio.md", "AIzaSyDkcwCPbSP4r8i3S6XLQtLRGQPJjVDwkGQ", argv[3]);

	}

	return 0;
}
