/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Structure definitions
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <sys/stat.h>
    #include <dirent.h>

typedef struct file_info_s {
    char *name;
    struct stat info;
    time_t mtime;
} file_info_t;

#endif
