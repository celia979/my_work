/*
** EPITECH PROJECT, 2025
** get_nb_len.c
** File description:
** nb_len
*/

#include "my.h"

int get_nb_len(long nb)
{
    int i = 1;

    if (nb < 0) {
        nb = -nb;
        i = i + 1;
    }
    while (nb >= 10) {
        nb = nb / 10;
        i = i + 1;
    }
    return (i);
}
