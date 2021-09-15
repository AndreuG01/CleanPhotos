//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#ifndef CLEANPHOTOS_LINKED_LIST_H
#define CLEANPHOTOS_LINKED_LIST_H

typedef struct _node {
    char file_name[2000]; // The directory where the file is located, with the name of the file without extension
    char full_path_file[2000]; // The directory where the file is located, with the name and extension
    char extension[20]; // The extension of the file
    struct _node *next;
} Node;


typedef struct _linkedList {
    Node *first;
    Node *last;
    int num_nodes;
} LinkedList;


LinkedList *init_list(LinkedList *list);
LinkedList *add_node_as_last(LinkedList *list, char *file_name, char *full_path_file, char *extension);
LinkedList *delete_node(LinkedList *list, Node *node);
Node *find_node_in_list(LinkedList *list, const char *file_name);
char *find_word_in_list(LinkedList *list, const char *file_name);
void clear_list(LinkedList *list);
void print_list(LinkedList *list);

#endif //CLEANPHOTOS_LINKED_LIST_H
