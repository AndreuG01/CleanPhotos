//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#include "headers/utils.h"

#include <stdio.h>
#include <stdlib.h>

void *check_malloc(void *pointer, char *msg, int error_code) {
    if (pointer == NULL) {
        printf("%s\n", msg);
        exit(error_code);
    } else {
        return pointer;
    }
}

int power(int num, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= num;
    }

    return res;
}