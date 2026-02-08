#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/scanner.h"

/*
 * Reads the contents of a directory and collects regular file names.
 *
 * Parameters:
 *  dir         - path to the directory to be scanned
 *  num_of_dir  - pointer to a counter storing the number of files found
 *  files       - fixed-size array to store file names (max 100 chars each)
 *
 * Behavior:
 *  - Opens the directory
 *  - Iterates over directory entries
 *  - Filters regular files (DT_REG)
 *  - Ignores hidden files (starting with '.')
 *  - Stores file names into the provided array
 *
 * Notes:
 *  - The function updates num_of_dir in place
 *  - The array is not dynamically allocated
 */
void *read_dir(const char *dir, int *num_of_dir, char (*files)[100]) {

    // Open directory stream
    DIR *stack = opendir(dir);
    const struct dirent *File;

    // Handle directory open failure
    if (!stack) {
        perror(dir);
        return NULL;
    }

    /*
     * Iterate through directory entries.
     * readdir returns NULL when no entries remain.
     */
    while ((File = readdir(stack)) != NULL) {

        // Process only regular files
        if (File->d_type == DT_REG) {

            // Skip hidden files
            if (File->d_name[0] != '.') {

                // Copy file name into buffer
                snprintf(files[*num_of_dir], 100, "%s", File->d_name);

                // Increment file counter
                (*num_of_dir)++;
            }
        }
    }

    /*
     * Optional terminator entry.
     * Indicates end of valid file names.
     */
    snprintf(files[*num_of_dir], 100, "%s", NULL);

    // Close directory stream
    closedir(stack);

    return NULL;
}