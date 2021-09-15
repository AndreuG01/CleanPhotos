//
// Created by Andreu Garcies Ramon on 9/9/21.
//

#include "headers/directory.h"

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "headers/utils.h"

extern int MALLOC_COUNT;
extern int FREE_COUNT;

int directory_can_be_opened(char *path) {
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return FALSE; // The path can not be opened
    } else {
        return TRUE; // The path can be opened
    }
}

/**
 *
 * @param table -> the table containing the "non-special files"
 * @param list -> the list containing all the aae and the mov files
 * @param edited_flag -> indicates if the edited flag is active
 * @param live_flag -> indicates if the live flag is active
 * @param verbose_flag -> indicates if the verbose flag is active
 * @param file_counter -> counts the number of files that are deleted
 */

void delete_files(HashTable *table, LinkedList *list, int edited_flag, int live_flag, int verbose_flag, int *file_counter) {
    Node *current_node = list->first, *tmp_node;
    while (current_node != NULL) {
        tmp_node = current_node->next;
        if (strcmp(current_node->extension, AAE_EXTENSION) == 0 && edited_flag == TRUE) {
            Node *original_file = find_in_table(table, current_node->file_name);
            Node *edited_file = find_in_table(table, get_edited_name(current_node->file_name));
            if (original_file != NULL && edited_file != NULL) {
                // The original, edited and editing file exist.
                if (verbose_flag == TRUE) {
                    printf("%sRemoving: %s%s\n", RED_COLOR, NORMAL_COLOR, original_file->full_path_file);
                }
                remove(original_file->full_path_file); // Remove the original file
                *file_counter += 1;
            }
            if (verbose_flag == TRUE) {
                printf("%sRemoving: %s%s\n", RED_COLOR, NORMAL_COLOR, current_node->full_path_file);
            }
            remove(current_node->full_path_file); // Delete the editing file
            delete_node(list, current_node);
            *file_counter += 1;
        }

        if (strcmp(current_node->extension, MOV_EXTENSION) == 0 && live_flag == TRUE) {
            Node *image = find_in_table(table, current_node->file_name);
            if (image != NULL) {
                // The image and the live mode image exist
                if (verbose_flag == TRUE) {
                    printf("%sRemoving: %s%s\n", RED_COLOR, NORMAL_COLOR, current_node->full_path_file);
                }
                remove(current_node->full_path_file); // Remove the mov file
                delete_node(list, current_node);
                *file_counter += 1;
            }
        }
        current_node = tmp_node;

    }
}


void process_dir(char *path, HashTable *table, LinkedList *list, int edited_flag, int live_flag, int recursive_flag) {
    DIR *dir_pointer = opendir(path);
    if (dir_pointer == NULL) {
        printf("%s: %s\n", DIR_OPENED_WRONG_MSG, path);
        exit(DIR_NOT_OPENED_EXIT_CODE);
    }

    struct dirent *entity;
    entity = readdir(dir_pointer);

    while (entity != NULL) {
        char *entity_extension = get_extension(entity->d_name);
        char *entity_name = get_name(entity->d_name, path);
        char *full_path_file = build_full_path_file(path, entity->d_name, FALSE);
        //if (entity_extension != NULL) {
        if (entity->d_type == DT_REG) {
            int special_file_found = FALSE;
            if (edited_flag == TRUE && live_flag == TRUE) {
                if (strcmp(entity_extension, AAE_EXTENSION) == 0 || strcmp(entity_extension, MOV_EXTENSION) == 0) {
                    add_node_as_last(list, entity_name, full_path_file, entity_extension);
                    special_file_found = TRUE;
                }
            } else if (edited_flag == FALSE) {
                if (strcmp(entity_extension, MOV_EXTENSION) == 0) {
                    add_node_as_last(list, entity_name, full_path_file, entity_extension);
                    special_file_found = TRUE;
                }
            } else if (live_flag == FALSE) {
                if (strcmp(entity_extension, AAE_EXTENSION) == 0) {
                    add_node_as_last(list, entity_name, full_path_file, entity_extension);
                    special_file_found = TRUE;
                }
            }
            if (special_file_found == FALSE) {
                add_to_table(table, entity_name, full_path_file, entity_extension);
            }
            //free(entity_extension);
            //FREE_COUNT += 1;
            //free(entity_name);
            //FREE_COUNT += 1;
            //free(full_path_file);
            //FREE_COUNT += 1;

        } else if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0 && recursive_flag == TRUE) {
            process_dir(full_path_file, table, list, edited_flag, live_flag, recursive_flag);
        }
        //}
        entity = readdir(dir_pointer);
    }
    closedir(dir_pointer);
}