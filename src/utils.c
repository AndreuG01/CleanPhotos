//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void *check_malloc(void *pointer, char *msg, int error_code) {
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

        return lower_str;
    }
}

char *get_extension(char *file_name) {
    int length = (int)strlen(file_name);
    char *extension = malloc(sizeof(char) * 100), *ptr = &file_name[length - 1];

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
    char *file_name = malloc(sizeof(char) * 100), *file_name_ptr = file_name;
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
        return build_full_path_file(path, name);
    } else {
        // We copy each character into file_name until we reach the address where the point has been found (previously
        // found)
        while (name_ptr != last_point_ptr) {
            *file_name_ptr = *name_ptr;
            name_ptr++; file_name_ptr++;
        }
        *file_name_ptr = '\0';

        return build_full_path_file(path, file_name);
    }
}

char *get_edited_name(char *name_file) {
    int length = (int)strlen(name_file);
    char *edited_name = malloc(sizeof(char) * (length + 2)), *name_file_ptr = name_file, *edited_name_ptr = edited_name;

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

char *build_full_path_file(char *path, char *name_file) {
    char *full_path = malloc(sizeof(char) * 1000);
    strcat(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, name_file);

    return full_path;
}