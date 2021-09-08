#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers/utils.h"
#include "headers/linked_list.h"
#include "headers/hash_table.h"

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


void print_white_spaces(int num_spaces) {
    for (int i = 0; i < num_spaces * 2; i++) {
        printf(" ");
    }
}

void list_files(char *path, int level) {
    DIR *dir_pointer = opendir(path);

    if (dir_pointer == NULL) {
        printf("Could not open directory %s\n", path);
        exit(2);
    }

    struct dirent *entity;
    entity = readdir(dir_pointer);
    while (entity != NULL) {
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            print_white_spaces(level);
            printf("%sOPENING DIR -> %s", BLUE, NORMAL_COLOR);
        } else if (entity->d_type == DT_REG) {
            print_white_spaces(level);
            printf("%s%s -> %s", GREEN, to_lower(get_extension(entity->d_name)), NORMAL_COLOR);
        }
        if (strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            printf("%s (%d)\n", entity->d_name, hash_mod(entity->d_name, N));
        }

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {

            unsigned long length_current_path = strlen(path);
            //char *new_path = malloc(sizeof(char) * (length_current_path + entity->d_namlen) + 1);
            // TODO: Re-do this properly
            char *new_path = malloc(sizeof(char) * 500);

            strcat(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, entity->d_name);

            list_files(new_path, level + 1);
        }

        entity = readdir(dir_pointer);
    }
    closedir(dir_pointer);
}


char *remove_extension(char *name) {
    unsigned long len_name = strlen(name);
    char *name_ptr = name[len_name - 1];
    while (*name_ptr != '.') {
        name_ptr--;
    }
}


void delete_files_edited_flag(char *path, HashTable *table) {
    DIR *dir_pointer = opendir(path);
    if (dir_pointer == NULL) {
        printf("%s: %s\n", DIR_OPENED_WRONG_MSG, path);
        exit(DIR_NOT_OPENED_EXIT_CODE);
    }

    struct dirent *entity;
    entity = readdir(dir_pointer);


    while (entity != NULL) {
        if (entity->d_type == DT_REG && strcmp(get_extension(entity->d_name), "aae") == 0) {
            char *full_path_files = malloc(sizeof(char) * 1000);
            strcat(full_path_files, path);
            strcat(full_path_files, "/");
            strcat(full_path_files, entity->d_name);

            //add_to_table(table, entity->d_name, full_path_files, get_extension(entity->d_name));
        } else if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            // TODO: Re-do this properly
            char *new_path = malloc(sizeof(char) * 500);

            strcat(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, entity->d_name);

            delete_files_edited_flag(new_path, table);
        }
            entity = readdir(dir_pointer);
    }
    closedir(dir_pointer);
}

int get_flags(int argc, char *argv[]) {
    int status = NO_FLAG;
    if (argc == 1) {
        return NO_FLAG;
    }
    if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--edited") == 0) {
        if (argc >= 3 && (strcmp(argv[2], "-l") == 0 || strcmp(argv[2], "--live") == 0)) {
            status = EDITED_AND_LIVE;
        } else {
            status = EDITED;
        }
    } else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--live") == 0) {
        if (argc >= 3 && (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "--edited") == 0)) {
            status = EDITED_AND_LIVE;
        } else {
            status = LIVE;
        }
    }

    return status;
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
    char *suggested_path = malloc(sizeof(char) * 1000);
    int i;
    for (i = flags + 1; i < argc - 1; i++) {
        strcat(suggested_path, argv[i]);
        strcat(suggested_path, " ");
    }
    strcat(suggested_path, argv[i]);

    return suggested_path;
}


int directory_can_be_opened(char *path) {
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return FALSE; // The path can not be opened
    } else {
        return TRUE; // The path can be opened
    }
}



int main(int argc, char *argv[]) {

    int status = get_flags(argc, argv), num_flags;
    if (status == NO_FLAG) {
        num_flags = 0;
        printf("No flags have been given\n");
    } else if (status == EDITED_AND_LIVE) {
        num_flags = 2;
        printf("Edited and live\n");
    } else if (status == EDITED) {
        num_flags = 1;
        printf("Edited\n");
    } else if (status == LIVE) {
        num_flags = 1;
        printf("Live\n");
    }

    if (argc == 1) {
        printf("%s\n", WRONG_ARGS_MSG);
        exit(WRONG_ARGS_EXIT_CODE);
    } else {
        // PATH SUGGESTION
        char *suggested_path = suggest_valid_path(argc, argv, num_flags);
        printf("Trying to access the directory: %s\n", suggested_path);

        if (directory_can_be_opened(suggested_path) == TRUE) {
            printf("%s\n", DIR_OPENED_CORRECT_MSG);
            if (status == EDITED) {
                HashTable table;
                init_hash_table(&table, "FLag EDITED");
                delete_files_edited_flag(suggested_path, &table);
                print_hash_table(&table);
            }
            //list_files(suggested_path, 0);
        } else {
            printf("%s %s\n",DIR_OPENED_WRONG_MSG, suggested_path);
            exit(DIR_NOT_OPENED_EXIT_CODE);
        }
    }




    return 0;
}
