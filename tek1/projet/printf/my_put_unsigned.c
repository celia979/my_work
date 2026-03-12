/*
** EPITECH PROJECT, 2026
** my_put_unsigned.c
** File description:
** unsigned
*/

#include "my.h"

int my_put_unsigned(unsigned int nb)
{
    int count = 0;

    if (nb >= 10) {
        count += my_put_unsigned(nb / 10);
    }
    count += my_putchar((nb % 10) + '0');
    return count;
}
