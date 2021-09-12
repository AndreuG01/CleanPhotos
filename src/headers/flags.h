//
// Created by Andreu Garcies Ramon on 12/9/21.
//

#ifndef CLEANPHOTOS_FLAGS_H
#define CLEANPHOTOS_FLAGS_H

int flags_are_correct(int argc, char *argv[]);
int find_flag(char *flag_to_find, int argc, char *argv[]);
int no_flags(int edited_flag, int live_flag, int rec_flag);

#endif //CLEANPHOTOS_FLAGS_H
