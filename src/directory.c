//
// Created by Andreu Garcies Ramon on 9/9/21.
//

#include "headers/directory.h"

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "headers/utils.h"

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
 * @param table -> the table containing all the other files
 * @param list -> the list containing all the mov and aae files
 */
void edited_removal(HashTable *table, LinkedList *list) {
    Node *original_file, *edited_file, *current_node = list->first;
    while (current_node != NULL) {
        original_file = find_in_table(table, current_node->file_name);
        edited_file = find_in_table(table, get_edited_name(current_node->file_name));
        if (edited_file != NULL && original_file != NULL) {
            // Both edited and original file exist so we have to remove the original one
            remove(original_file->full_path_file);
        }
        if (strcmp(current_node->extension, AAE_EXTENSION) == 0) {
            // Now we can remove the aae file
            remove(current_node->full_path_file);
            delete_node(list, current_node);
        }
        current_node = current_node->next;
    }
}

/**
 *
 * @param table -> the table containing all the other files
 * @param list -> the list containing all the mov and aae files
 */
void live_removal(HashTable *table, LinkedList *list) {
    Node *current_node = list->first;
    while (current_node != NULL) {
        Node *image = find_in_table(table, current_node->file_name); // The image corresponding to the mov file
        if (image != NULL) {
            // If the image is found, then we do not want to maintain the mov file and we can remove it
            remove(current_node->full_path_file);
        }
        if (strcmp(current_node->extension, MOV_EXTENSION) == 0) {
            delete_node(list, current_node);
        }
        current_node = current_node->next;
    }
}

void delete_files(char *path, HashTable *table, LinkedList *list, int edited_flag, int live_flag) {
    DIR *dir_pointer = opendir(path);
    if (dir_pointer == NULL) {
        printf("%s: %s\n", DIR_OPENED_WRONG_MSG, path);
        exit(DIR_NOT_OPENED_EXIT_CODE);
    }

    struct dirent *entity;
    entity = readdir(dir_pointer);

    while (entity != NULL) {
        char *entity_extension = get_extension(entity->d_name);
        char *entity_name = get_name(entity->d_name);
        char *full_path_file = build_full_path_file(path, entity->d_name);
        if (entity_extension != NULL) {
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
            } else if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
                delete_files(full_path_file, table, list, edited_flag, live_flag);
            }
        }
        entity = readdir(dir_pointer);
    }
    closedir(dir_pointer);

    if (edited_flag == TRUE) {
        edited_removal(table, list);
    }
    if (live_flag == TRUE) {
        live_removal(table, list);
    }
}