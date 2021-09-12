//
// Created by Andreu Garcies Ramon on 12/9/21.
//

#include "headers/flags.h"
#include "headers/utils.h"

#include <string.h>

int flags_are_correct(int argc, char *argv[]) {
    if (argc == 1) {
        return FALSE;
    }
    for (int i = 1; i < argc - 1; i++) {
        if (!(strcmp(argv[i], EDITED_FLAG_SHORT) == 0 || strcmp(argv[i], EDITED_FLAG_LONG) == 0 || strcmp(argv[i], LIVE_FLAG_SHORT) == 0
              || strcmp(argv[i], LIVE_FLAG_LONG) == 0 || strcmp(argv[i], RECURSIVE_FLAG_SHORT) == 0 || strcmp(argv[i], RECURSIVE_FLAG_LONG) == 0)) {
            return FALSE;
        }
    }

    return TRUE;
}

int find_flag(char *flag_to_find, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(flag_to_find, argv[i]) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}


int no_flags(int edited_flag, int live_flag, int rec_flag) {
    if (edited_flag == FALSE && live_flag == FALSE && rec_flag == FALSE) {
        return TRUE;
    }

    return FALSE;
}