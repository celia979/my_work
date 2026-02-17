/*
** EPITECH PROJECT, 2025
** my_revstr.c
** File description:
** yes
*/

#include <unistd.h>
#include <string.h>
#include "../../include/my.h"

char *my_revstr(char *str)
{
    int y = 0;
    int r = strlen(str) - 1;
    char t;

    while (y < r) {
        t = str[y];
        str[y] = str[r];
        str[r] = t;
        y++;
        r--;
    }
    my_putstr(str);
    return str;
}
