#include <stdio.h>
#include "../includes/parser.h"

/*
 * Prints a fixed-size array of strings.
 *
 * Parameters:
 *  len  - length of each string
 *  num  - number of strings to print
 *  text - 2D char array containing the strings
 *
 * Behavior:
 *  - Iterates through the array
 *  - Prints each string to stdout
 */
void print_f(int len, int num, char (*text)[len]) {

    for (int i = 0; i < num; i++) {
        printf("%s", text[i]);
    }
}

/*
 * Reads a text file line by line into a fixed buffer.
 *
 * Parameters:
 *  file - path to the file to be read
 *  text - destination buffer (max 100 lines, 100 chars each)
 *
 * Returns:
 *  - Number of lines read on success
 *  - -1 if file could not be opened
 *
 * Behavior:
 *  - Opens file in read mode
 *  - Reads up to 100 lines
 *  - Stops on EOF or buffer limit
 */
int read_file(char *file, char (*text)[100]) {

    int i = 0;
    FILE *f = fopen(file, "r");

    if (!f)
        return -1;

    while (i < 100 && fgets(*(text + i), 100, f) != NULL) {
        i++;
    }

    fclose(f);
    return i;
}