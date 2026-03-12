/*
** EPITECH PROJECT, 2026
** tools.c
** File description:
** nb
*/

#include "my.h"

int get_nb(const char *format, int *i)
{
    int nb = 0;

    while (format[*i] >= '0' && format[*i] <= '9') {
        nb = (nb * 10) + (format[*i] - '0');
        *i = *i + 1;
    }
    return (nb);
}
