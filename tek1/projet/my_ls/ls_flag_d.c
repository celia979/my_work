/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Flag -d implementation
*/

#include "include/my.h"

int flag_d(char const *filepath, int flags)
{
    struct stat info;

    if (lstat(filepath, &info) == -1) {
        perror(filepath);
        return 84;
    }
    if (flags & FLAG_L)
        print_long_format(".", filepath);
    else {
        my_putstr(filepath);
        my_putchar('\n');
    }
    return 0;
}
