/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Main header file
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <pwd.h>
    #include <grp.h>
    #include <time.h>
    #include <string.h>
    #include "struct.h"

    #define FLAG_L 1
    #define FLAG_A 2
    #define FLAG_R_MAJ 4
    #define FLAG_D 8
    #define FLAG_T 16

int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_ls(char const *filepath, int flags);
int flag_a(char const *filepath, int flags);
int flag_l(char const *filepath, int flags);
int flag_d(char const *filepath, int flags);
int flag_t(char const *filepath, int flags);
int flag_r_maj(char const *filepath, int flags);
void print_long_format(char const *filepath, char const *name);
void print_permissions(mode_t mode);
int compare_time(const void *a, const void *b);
int error(const char *filepath);

#endif
