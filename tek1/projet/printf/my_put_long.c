/*
** EPITECH PROJECT, 2026
** my_printf.c
** File description:
** puts a long
*/
#include "my.h"

int my_put_long(long nb)
{
    int count = 0;

    if (nb < 0) {
        count = count + my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        count = count + my_put_long(nb / 10);
    count = count + my_putchar((nb % 10) + '0');
    return count;
}
