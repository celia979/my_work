/*
** EPITECH PROJECT, 2026
** my_put_hex.c
** File description:
** hexadecimal
*/

#include "my.h"

int my_put_hex_lower(unsigned int nb)
{
    char *base = "0123456789abcdef";
    int count = 0;

    if (nb >= 16) {
        count += my_put_hex_lower(nb / 16);
    }
    count += my_putchar(base[nb % 16]);
    return count;
}

int my_put_hex_upper(unsigned int nb)
{
    char *base = "0123456789ABCDEF";
    int count = 0;

    if (nb >= 16) {
        count += my_put_hex_upper(nb / 16);
    }
    count += my_putchar(base[nb % 16]);
    return count;
}
