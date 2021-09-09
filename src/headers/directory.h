//
// Created by Andreu Garcies Ramon on 9/9/21.
//

#ifndef CLEANPHOTOS_DIRECTORY_H
#define CLEANPHOTOS_DIRECTORY_H

#include "hash_table.h"
#include "linked_list.h"

int directory_can_be_opened(char *path);
void delete_files(char *path, HashTable *table, LinkedList *list, int edited_flag, int live_flag);

#endif //CLEANPHOTOS_DIRECTORY_H
