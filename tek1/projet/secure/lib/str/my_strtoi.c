/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** my_strtoi
*/

#include "my_str.h"

int my_strtoi(char *str)
{
    int nb = 0;
    int neg = 0;

    if (str[0] == '-')
        neg = 1;
    for (int i = neg; str[i] != '\0'; i++) {
        nb *= 10;
        nb += str[i] - 48;
    }
    if (neg == 1)
        return - nb;
    return nb;
}
