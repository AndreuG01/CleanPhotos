//
// Created by Andreu Garcies Ramon on 12/9/21.
//

#include "headers/path.h"
#include "headers/utils.h"

#include <string.h>
#include <stdlib.h>

char *build_full_path_file(char *path, char *name_file, int need_free) {
    char *full_path = check_malloc(malloc(sizeof(char) * 1000), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE);
    int length_path = (int)strlen(path);
    strcat(full_path, path);
    if (strcmp(&path[length_path - 1], "/") != 0) {
        strcat(full_path, "/");
    }
    strcat(full_path, name_file);
    if (need_free == TRUE) {
        //free(name_file);
        //FREE_COUNT += 1;
    }

    return full_path;
}

/**
 *
 * @param argc -> the number of arguments that the array has
 * @param flags -> the number of flags, to determine from where the path has to be taken from
 * @param argv -> the arguments that the program has received
 * @return -> a possible valid path obtained from the given arguments
 */
char *suggest_valid_path(int argc, char *argv[], int flags) {
    // TODO: allocate the necessary memory
    char *suggested_path = check_malloc(malloc(sizeof(char) * 1000), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE);

    int i;
    for (i = flags + 1; i < argc - 1; i++) {
        strcat(suggested_path, argv[i]);
        strcat(suggested_path, " ");
    }
    strcat(suggested_path, argv[i]);

    return suggested_path;
}