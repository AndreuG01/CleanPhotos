//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/hash_table.h"

#include <string.h>
#include <stdio.h>


#include "headers/utils.h"


// TODO: find an optimal hash function
int hash_mod(char *data, int n) {
    int l = strlen(data);
    char c;
    unsigned long long int total = 0;
    for (int i = 0; i < l; i++) {
        c = data[i];
        total += c * i;
    }

    return total % n;
}


HashTable *init_hash_table(HashTable *table, char *name) {
    //HashTable *table = check_malloc(malloc(sizeof(HashTable)), MALLOC_WRONG_MSG, MALLOC_WRONG_EXIT_CODE);

    for (int i = 0; i < N; i++) {
        init_list(&table->list[i]);
    }
    table->elements_in_table = 0;
    table->name = name;

    return table;
}

Node *find_in_table(HashTable *table, char *name) {
    int key = hash_mod(name, N);
    return find_node_in_list(&table->list[key], name);
}


HashTable *add_to_table(HashTable *table, char *file_name, char *full_path_file, char *extension) {
    // We will add every element regardless if it is already in the table
    int key = hash_mod(file_name, N);
    //printf("%s --> KEY %d\n", file_name, key);
    add_node_as_last(&table->list[key], file_name, full_path_file, extension);
    table->elements_in_table += 1;

    return table;
}


void clear_hash_table(HashTable *table) {
    for (int i = 0; i < N; i++) {
        clear_list(&table->list[i]);
    }
}


void print_hash_table(HashTable *table) {
    printf("---%d ELEMENTS IN TOTAL---\n", table->elements_in_table);

    for (int i = 0; i < N; i++) {
        if (table->list[i].first != NULL) {
            printf("---Bucket %d---\n", i);
            print_list(&table->list[i]);
            printf("-------------\n");
        }
    }

}