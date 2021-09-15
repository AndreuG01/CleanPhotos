#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/utils.h"
#include "headers/linked_list.h"
#include "headers/hash_table.h"
#include "headers/directory.h"
#include "headers/flags.h"
#include "headers/path.h"

extern int MALLOC_COUNT;
extern int FREE_COUNT;


int main(int argc, char *argv[]) {


    int edited_flag = find_flag(EDITED_FLAG_SHORT, argc, argv) || find_flag(EDITED_FLAG_LONG, argc, argv);
    int live_flag = find_flag(LIVE_FLAG_SHORT, argc, argv) || find_flag(LIVE_FLAG_LONG, argc, argv);
    int recursive_flag = find_flag(RECURSIVE_FLAG_SHORT, argc, argv) || find_flag(RECURSIVE_FLAG_LONG, argc, argv);
    int verbose_flag = find_flag(VERBOSE_FLAG_SHORT, argc, argv) || find_flag(VERBOSE_FLAG_LONG, argc, argv);
    int num_flags = edited_flag + live_flag + recursive_flag + verbose_flag;

    if (flags_are_correct(argc, argv) == TRUE && no_flags(edited_flag, live_flag, recursive_flag) == FALSE) {


        /*if (argc == 1) {
            printf("%s\n", WRONG_ARGS_MSG);
            exit(WRONG_ARGS_EXIT_CODE);
        } else {*/

        // PATH SUGGESTION
        char *suggested_path = suggest_valid_path(argc, argv, num_flags);
        if (verbose_flag == TRUE) {
            printf("Trying to access the directory: %s\n", suggested_path);
        }

        if (directory_can_be_opened(suggested_path) == TRUE) {
            if (verbose_flag == TRUE) {
                printf("%s\n", DIR_OPENED_CORRECT_MSG);
            }
            int num_deleted_files = 0;
            LinkedList list;
            init_list(&list);
            HashTable table;
            init_hash_table(&table, "Table");
            process_dir(suggested_path, &table, &list, edited_flag, live_flag, recursive_flag);
            delete_files(&table, &list, edited_flag, live_flag, verbose_flag, &num_deleted_files);

            if (verbose_flag == TRUE) {
                printf("\n%d FILES have been %sprocessed%s\n", list.num_nodes + table.elements_in_table, GREEN_COLOR, NORMAL_COLOR);
                printf("%d FILES have been %sdeleted%s\n", num_deleted_files, RED_COLOR, NORMAL_COLOR);
            }

            clear_list(&list);
            clear_hash_table(&table);
        } else {
            printf("%s %s\n",DIR_OPENED_WRONG_MSG, suggested_path);
            exit(DIR_NOT_OPENED_EXIT_CODE);
        }
        //free(suggested_path);
        //FREE_COUNT += 1;
        //}
    } else {
        // If the user has not introduced any flag, or one of the flags is incorrect, a help menu is displayed to show
        // the behaviour of the program
        print_help();
    }

    //printf("MALLOCS: %d\n", MALLOC_COUNT);
    //printf("FREES: %d\n", FREE_COUNT);

    return 0;
}
