//
// Created by Andreu Garcies Ramon on 28/8/21.
//

#ifndef CLEANPHOTOS_UTILS_H
#define CLEANPHOTOS_UTILS_H


// Flag strings
#define EDITED_FLAG_SHORT "-e"
#define EDITED_FLAG_LONG "--edited"
#define LIVE_FLAG_SHORT "-l"
#define LIVE_FLAG_LONG "--live"
#define RECURSIVE_FLAG_SHORT "-r"
#define RECURSIVE_FLAG_LONG "--recursive"
#define VERBOSE_FLAG_SHORT "-v"
#define VERBOSE_FLAG_LONG "--verbose"



#define TRUE 1
#define FALSE 0

#define DIR_OPENED_CORRECT_MSG "The directory has been opened correctly"
#define DIR_OPENED_WRONG_MSG "Could not open the directory: "
#define MALLOC_WRONG_MSG "Memory allocation went wrong"

// Color codes
#define RED_COLOR "\x001b[31m"
#define NORMAL_COLOR "\x001b[0m"
#define GREEN_COLOR "\x001b[32m"

// Error codes
#define DIR_NOT_OPENED_EXIT_CODE 100
#define MALLOC_WRONG_EXIT_CODE 104

// Possible flag codes
#define AAE_EXTENSION "aae"
#define MOV_EXTENSION "mov"

void *check_malloc(void *pointer, char *msg, int error_code);
char *to_lower(char *str);
char *get_extension(char *file_name);
char *get_name(char *name, char *path);
char *get_edited_name(char *name_file);
char *build_full_path_file(char *path, char *name_file, int need_free);
void print_help();

#endif //CLEANPHOTOS_UTILS_H
