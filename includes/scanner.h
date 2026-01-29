#ifndef SCANNER_H
#define SCANNER_H

#include <dirent.h>

void *read_dir(const char *dir, int *num_of_dir, char (*files)[100]);

#endif
