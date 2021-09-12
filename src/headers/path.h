//
// Created by Andreu Garcies Ramon on 12/9/21.
//

#ifndef CLEANPHOTOS_PATH_H
#define CLEANPHOTOS_PATH_H

char *build_full_path_file(char *path, char *name_file, int need_free);
char *suggest_valid_path(int argc, char *argv[], int flags);

#endif //CLEANPHOTOS_PATH_H
