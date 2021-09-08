//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/linked_list.h"
#include "headers/utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *new_dyn_node(char *file_name, char *full_path_file, char *extension) {
    Node *node = check_malloc(malloc(sizeof(Node)), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE);

    strcpy(node->file_name, file_name);
    strcpy(node->full_path_file, full_path_file);
    strcpy(node->extension, extension);
    node->next = NULL;

    return node;
}


LinkedList *init_list(LinkedList *list) {
    //LinkedList *list = malloc(sizeof(LinkedList));
    list->first = NULL;
    list->last = NULL;

    return list;
}


LinkedList *add_node_as_last(LinkedList *list, char *file_name, char *full_path_file, char *extension) {
    Node *node = new_dyn_node(file_name, full_path_file, extension);

    if (list->first == NULL && list->last == NULL) {
        list->last = node;
        list->first = node;
    } else {
        list->last->next = node;
        list->last = node;
    }

    return list;
}


char *find_word_in_list(LinkedList *list, const char *file_name) {
    Node *tmp_node = list->first;
    while (tmp_node != NULL) {
        if (tmp_node->file_name == file_name) {
            return tmp_node->file_name;
        }
        tmp_node = tmp_node->next;
    }

    return NULL; // The data that we are searching for is not found
}



void clear_list(LinkedList *list) {
    if (list != NULL) {
        Node *tmp_node = list->first;
        while (tmp_node != NULL) {
            list->first = tmp_node->next;
            free(tmp_node);
            tmp_node = list->first;
        }
    }
}


void print_list(LinkedList *list) {
    Node *tmp_node = list->first;

    while (tmp_node != NULL) {
        printf("%s --> (%s)\n", tmp_node->file_name, tmp_node->full_path_file);
        tmp_node = tmp_node->next;
    }
}