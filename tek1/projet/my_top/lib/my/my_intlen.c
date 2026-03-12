/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** my_intlen
*/

#include "my.h"

int my_intlen(int nb)
{
    int len = 1;

    if (nb > 0) {
        while (nb < len * 10)
            len *= 10;
    } else {
        while (-(nb) < len * 10)
            len *= 10;
        len *= 10;
    }
    return len / 10;
}
