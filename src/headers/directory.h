//
// Created by Andreu Garcies Ramon on 9/9/21.
//

#ifndef CLEANPHOTOS_DIRECTORY_H
#define CLEANPHOTOS_DIRECTORY_H

#include "hash_table.h"
#include "linked_list.h"

int directory_can_be_opened(char *path);
void delete_files(HashTable *table, LinkedList *list, int edited_flag, int live_flag, int verbose_flag, int *file_counter);
void process_dir(char *path, HashTable *table, LinkedList *list, int edited_flag, int live_flag, int recursive_flag);

#endif //CLEANPHOTOS_DIRECTORY_H
