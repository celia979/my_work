/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Main file for my_ls project
*/

#include "include/my.h"

static int parse_flags(char const *arg)
{
    int flags = 0;
    int i = 1;

    if (arg[0] != '-')
        return -1;
    while (arg[i] != '\0') {
        if (arg[i] == 'l')
            flags |= FLAG_L;
        if (arg[i] == 'a')
            flags |= FLAG_A;
        if (arg[i] == 'R')
            flags |= FLAG_R_MAJ;
        if (arg[i] == 'd')
            flags |= FLAG_D;
        if (arg[i] == 't')
            flags |= FLAG_T;
        i++;
    }
    return flags;
}

int my_ls(char const *filepath, int flags)
{
    if (flags & FLAG_R_MAJ)
        return flag_r_maj(filepath, flags);
    if (flags & FLAG_D)
        return flag_d(filepath, flags);
    if (flags & FLAG_T)
        return flag_t(filepath, flags);
    return flag_a(filepath, flags);
}

static int process_args(int ac, char **av, int *flags)
{
    int i = 1;
    int file_count = 0;

    while (i < ac && av[i][0] == '-') {
        *flags |= parse_flags(av[i]);
        i++;
    }
    file_count = ac - i;
    if (file_count == 0)
        my_ls(".", *flags);
    else {
        while (i < ac) {
            my_ls(av[i], *flags);
            i++;
        }
    }
    return 0;
}

int main(int ac, char **av)
{
    int flags = 0;

    if (ac == 1) {
        my_ls(".", 0);
        return 0;
    }
    return process_args(ac, av, &flags);
}
