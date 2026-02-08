#include <stdio.h>
#include <stdlib.h>
#include "../includes/scanner.h"
#include "../includes/parser.h"

/*
 * Compares two strings for equality.
 *
 * Parameters:
 *  a - first string
 *  b - second string
 *
 * Returns:
 *  - 1 if strings are equal
 *  - 0 if strings differ
 *
 * Notes:
 *  - Performs character-by-character comparison
 *  - Stops at first difference or at string end
 */
int str_equals(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++;
        b++;
    }
    return *a == *b;
}

/*
 * Scans a directory and writes all regular file contents into "out.txt".
 *
 * Parameters:
 *  path - path to the target directory
 *
 * Behavior:
 *  - Allocates fixed buffers for file names and file contents
 *  - Reads directory entries using read_dir
 *  - Iterates over files, reading each one line by line
 *  - Writes file contents to "out.txt"
 *  - Frees allocated memory at the end
 *
 * Notes:
 *  - Only reads up to 100 files
 *  - Each file's lines are limited to 100 characters
 */
void run(char *path) {

    int num_of_dir = 0;

    // Allocate buffers for reading file contents and directory file names
    char (*text)[100] = malloc(100 * sizeof *text);
    char (*dirs)[100] = malloc(100 * sizeof *text);

    if (!text || !dirs) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Read directory entries
    read_dir(path, &num_of_dir, dirs);

    // Open output file for writing aggregated content
    FILE *out = fopen("out.txt", "w");
    if (!out) {
        perror("out.txt");
        free(text);
        free(dirs);
        return;
    }

    // Iterate over files in directory
    for (int i = 0; i < num_of_dir; i++) {

        char fullpath[256];

        // Construct full file path
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirs[i]);

        // Read file into buffer
        int lines = read_file(fullpath, text);
        if (lines <= 0) continue;

        // Write file contents to output
        for (int j = 0; j < lines; j++) {
            fprintf(out, "%s", text[j]);
        }
    }

    // Cleanup
    fclose(out);
    free(text);
    free(dirs);
}