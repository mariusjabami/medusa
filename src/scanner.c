#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/scanner.h"

void *read_dir(const char *dir, int *num_of_dir, char (*files)[100]){

	DIR *stack = opendir(dir);

	const struct dirent *File;

	if(!dir){ 
		perror(dir);
		return NULL;
	}

	while ((File = readdir(stack)) != NULL) {

		if (File->d_type == DT_REG) {
			if (File->d_name[0] != '.') {
				snprintf(files[*num_of_dir], 100, "%s%s", dir, File->d_name);
				(*num_of_dir)++;
			}
		}
	}

	snprintf(files[*num_of_dir], 100, "%s", NULL);

	closedir(stack);

	return NULL;
}
