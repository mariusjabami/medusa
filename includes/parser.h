#ifndef PARSE_H
#define PARSE_H

void print_f(int len, int num, char (*text)[len]);
void print_fdyn(int len, int num, char **dir);

int read_file(char *file, char (*text)[100]);

#endif
