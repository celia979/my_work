/*
** EPITECH PROJECT, 2026
** my_put_binary.c
** File description:
** binary
*/

#include "my.h"

int my_put_binary(unsigned int nb)
{
    int count = 0;

    if (nb >= 2)
        count = count + my_put_binary(nb / 2);
    count = count + my_putchar((nb % 2) + '0');
    return (count);
}
