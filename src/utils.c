//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int MALLOC_COUNT = 0;
int FREE_COUNT = 0;

void *check_malloc(void *pointer, char *msg, int error_code) {
    //MALLOC_COUNT += 1;
    if (pointer == NULL) {
        printf("%s\n", msg);
        exit(error_code);
    } else {
        return pointer;
    }
}

char *to_lower(char *str) {
    if (str == NULL) {
        return NULL;
    } else {
        static char lower_str[200];
        char *str_ptr = str, *lower_str_ptr = lower_str;
        while (*str_ptr != '\0') {
            *lower_str_ptr = (char)tolower((int)*str_ptr);;
            str_ptr++;
            lower_str_ptr++;
        }
        *lower_str_ptr = '\0';
        //free(str);
        //FREE_COUNT += 1;

        return lower_str;
    }
}

char *get_extension(char *file_name) {
    int length = (int)strlen(file_name);
    char *extension = check_malloc(malloc(sizeof(char) * 100), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE), *ptr = &file_name[length - 1];

    for (int i = length; i > 0; i--) {
        if (*ptr == '.') {
            ptr++;
            strcat(extension, ptr);
            return to_lower(extension);
        }
        ptr--;
    }

    return NULL; // The function returns NULL if the given file name has no extension
}


char *get_name(char *name, char *path) {
    int length = (int)strlen(name), i = length;
    char *last_point_ptr = &name[length - 1], *name_ptr = name;
    char *file_name = check_malloc(malloc(sizeof(char) * 100), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE), *file_name_ptr = file_name;
    int  point_found = FALSE;
    // Finding the address where the extension is located
    while (point_found == FALSE && i > 0) {
        if (*last_point_ptr != '.') {
            last_point_ptr--;
        } else {
            point_found = TRUE;
        }
        i--;
    }
    if (point_found == FALSE) {
        // No point has been found, therefore we return the same name that we have received
        return build_full_path_file(path, name, FALSE);
    } else {
        // We copy each character into file_name until we reach the address where the point has been found (previously
        // found)
        while (name_ptr != last_point_ptr) {
            *file_name_ptr = *name_ptr;
            name_ptr++; file_name_ptr++;
        }
        *file_name_ptr = '\0';

        return build_full_path_file(path, file_name, TRUE);
    }
}

char *get_edited_name(char *name_file) {
    int length = (int)strlen(name_file);
    char *edited_name = check_malloc(malloc(sizeof(char) * (length + 2)), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE), *name_file_ptr = name_file, *edited_name_ptr = edited_name;

    while (*name_file_ptr != '\0') {
        *edited_name_ptr = *name_file_ptr;
        if (*name_file_ptr == '_') {
            *edited_name_ptr = *name_file_ptr;
            edited_name_ptr++; name_file_ptr++;
            *edited_name_ptr = 'E';
            edited_name_ptr++;
        } else {
            edited_name_ptr++;
            name_file_ptr++;
        }
    }
    *edited_name_ptr = '\0';

    return edited_name;
}

char *build_full_path_file(char *path, char *name_file, int need_free) {
    char *full_path = check_malloc(malloc(sizeof(char) * 1000), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE);
    strcat(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, name_file);
    if (need_free == TRUE) {
        //free(name_file);
        //FREE_COUNT += 1;
    }

    return full_path;
}