//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/linked_list.h"
#include "headers/utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int FREE_COUNT;

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
    list->num_nodes = 0;

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
    list->num_nodes += 1;

    return list;
}


LinkedList *delete_node(LinkedList *list, Node *node) {
    if (node == list->first && node == list->last) {
        // The node is the only one in the list
        list->first = node->next;
        list->last = node->next;
    } else if (node == list->first && node != list->last) {
        // The node is the first of the list
        list->first = node->next;
    } else {
        Node *tmp_node = list->first;
        while (tmp_node->next != node) {
            tmp_node = tmp_node->next;
        }
        if (node->next != NULL) {
            // The node is in the middle of the list
            tmp_node->next = node->next;
            node->next = NULL;
        } else if (node->next == NULL) {
            // The node is the last of the list
            tmp_node->next = node->next;
            list->last = tmp_node;
        }
    }
    list->num_nodes -= 1;

    return list;
}

Node *find_node_in_list(LinkedList *list, const char *file_name) {
    Node *tmp_node = list->first;
    while (tmp_node != NULL) {
        if (strcmp(tmp_node->file_name, file_name) == 0) {
            return tmp_node;
        }
        tmp_node = tmp_node->next;
    }
    return NULL;
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
            //free(tmp_node);
            //FREE_COUNT += 1;
            tmp_node = list->first;
        }
    }
}


void print_list(LinkedList *list) {
    Node *tmp_node = list->first;
    int counter = 1;
    while (tmp_node != NULL) {
        printf("%d) %s --> (%s)\n", counter, tmp_node->file_name, tmp_node->full_path_file);
        tmp_node = tmp_node->next;
        counter += 1;
    }
}