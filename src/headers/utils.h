//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#ifndef CLEANPHOTOS_UTILS_H
#define CLEANPHOTOS_UTILS_H

// Flag codes
#define NO_FLAG 0
#define EDITED 1
#define LIVE 2
#define EDITED_AND_LIVE 3


// Terminal colors escape codes
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1b[36m"

#define TRUE 1
#define FALSE 0

#define DIR_OPENED_CORRECT_MSG "The directory has been opened correctly"
#define DIR_OPENED_WRONG_MSG "Could not open the directory: "
#define WRONG_ARGS_MSG "The program should receive a directory"
#define MALLOC_WRONG_MSG "Memory allocation went wrong"



// Error codes
#define DIR_NOT_OPENED_EXIT_CODE 100
#define WRONG_ARGS_EXIT_CODE 102
#define MALLOC_WRONG_EXIT_CODE 104


void *check_malloc(void *pointer, char *msg, int error_code);
int power(int num, int exp);

#endif //CLEANPHOTOS_UTILS_H
