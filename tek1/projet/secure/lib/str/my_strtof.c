/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** my_strtof
*/

#include "my_str.h"

double my_strtof(char *str)
{
    double nb = 0;
    double decimal = 0.1;
    int neg = 0;
    int i = 0;

    if (str[0] == '-')
        neg = 1;
    for (i = neg; str[i] != '.'; i++) {
        nb *= 10;
        nb += str[i] - 48;
    }
    for (i += 1; str[i] != '\0'; i++) {
        nb += (str[i] - 48) * decimal;
        decimal /= 10;
    }
    if (neg == 1)
        return - nb;
    return nb;
}
