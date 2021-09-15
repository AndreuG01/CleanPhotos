//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#ifndef CLEANPHOTOS_HASH_TABLE_H
#define CLEANPHOTOS_HASH_TABLE_H

#include "linked_list.h"

#define N 1009


typedef struct _hashTable {
    LinkedList list[N];
    int elements_in_table;
    char *name;
} HashTable;

int hash_mod(char *data, int n);
HashTable *init_hash_table(HashTable *table, char *name);
HashTable *add_to_table(HashTable *table, char *file_name, char *full_path_file, char *extension);
Node *find_in_table(HashTable *table, char *name);
void print_hash_table(HashTable *table);
void clear_hash_table(HashTable *table);

#endif //CLEANPHOTOS_HASH_TABLE_H
