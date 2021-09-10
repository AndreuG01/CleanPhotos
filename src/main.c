#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/utils.h"
#include "headers/linked_list.h"
#include "headers/hash_table.h"
#include "headers/directory.h"

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
            int num_deleted_files = 0;
            LinkedList list;
            init_list(&list);
            HashTable table;
            init_hash_table(&table, "Table");
            if (status == EDITED) {
                process_dir(suggested_path, &table, &list, TRUE, FALSE);
                delete_files(&table, &list, TRUE, FALSE, &num_deleted_files);
            } else if (status == LIVE) {
                process_dir(suggested_path, &table, &list, FALSE, TRUE);
                delete_files(&table, &list, FALSE, TRUE, &num_deleted_files);
            } else if (status == EDITED_AND_LIVE) {
                process_dir(suggested_path, &table, &list, TRUE, TRUE);
                delete_files(&table, &list, TRUE, TRUE, &num_deleted_files);
            }
            printf("\n%d FILES have been deleted\n", num_deleted_files);
            clear_list(&list);
            clear_hash_table(&table);
        } else {
            printf("%s %s\n",DIR_OPENED_WRONG_MSG, suggested_path);
            exit(DIR_NOT_OPENED_EXIT_CODE);
        }
    }

    /*HashTable table; LinkedList list;
    init_hash_table(&table, "Table"); init_list(&list);
    int counter = 0;
    process_dir("../Test", &table, &list, TRUE, FALSE);
    delete_files(&table, &list, TRUE, FALSE, &counter);*/

    return 0;
}
