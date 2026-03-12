/*
** EPITECH PROJECT, 2026
** my_put_octal.c
** File description:
** my_put_octal
*/

#include "my.h"

int my_put_octal(unsigned int nb)
{
    int count = 0;

    if (nb >= 8) {
        count += my_put_octal(nb / 8);
    }
    count += my_putchar((nb % 8) + '0');
    return count;
}
