#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

/*
 * scanner.h
 * Core scanning module of Medusa.
 *
 * Responsible for:
 *  - Traversing directories recursively
 *  - Discovering source files
 *  - Triggering parsing for each valid file
 */
#include "../includes/scanner.h"

/*
 * parser.h
 * Source code analysis module.
 *
 * Responsible for:
 *  - Reading source files
 *  - Extracting relevant information
 *  - Producing raw analysis output
 */
#include "../includes/parser.h"

/*
 * utils.h
 * Utility helper functions shared across Medusa.
 *
 * Provides:
 *  - String comparison helpers
 *  - Common reusable routines
 */
#include "../includes/utils.h"

/*
 * server.h
 * AI integration layer.
 *
 * Responsible for:
 *  - Sending analysis results to Medusa AI
 *  - Receiving and generating formatted reports
 *  - Handling API authentication
 */
#include "../includes/server.h"

/*
 * Entry point of Medusa.
 *
 * Expected usage:
 *      ./program run <directory>
 *
 * Arguments:
 *      argc - number of arguments
 *      argv - argument vector
 *
 * Commands:
 *      run  - scans the given directory and generates an AI report
 */
int main(int argc, char **argv) {

    /*
     * Validate minimum number of arguments.
     * At least one command must be provided.
     */
    if (argc < 2) {
        printf("Usage: ./program <command>\n");
        return 1;
    }

    /*
     * If command is "run":
     * 1. Scan the provided directory
     * 2. Generate analysis report using Medusa AI
     */
    if (str_equals(argv[1], "run")) {

        /*
         * argv[2] should contain the target directory path.
         * Example:
         *      ./program run .
         */
        run(argv[2]);

        /*
         * Sends generated output to Medusa AI.
         *
         * Parameters:
         *  - "out.txt"      : raw analysis output
         *  - "relatorio.md" : final markdown report
         *  - API_KEY        : authentication token
         */
        analyze_with_medusa("out.txt", "relatorio.md", "API_KEY", argv[3]);
    }

    return 0;
}
