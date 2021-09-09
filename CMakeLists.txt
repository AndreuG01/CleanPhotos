cmake_minimum_required(VERSION 3.17)
project(CleanPhotos C)

set(CMAKE_C_STANDARD 99)

add_executable(CleanPhotos src/main.c
        src/hash_table.c src/headers/hash_table.h
        src/linked_list.c src/headers/linked_list.h
        src/headers/utils.h src/utils.c src/directory.c src/headers/directory.h)