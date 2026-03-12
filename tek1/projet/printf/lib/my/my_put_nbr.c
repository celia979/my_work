/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** yes
*/

#include <unistd.h>
#include "my.h"

int my_put_nbr(int nb)
{
    long n = nb;
    int len;

    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    len = get_nb_len(n);
    if (n >= 10) {
        my_put_nbr(n / 10);
    }
    my_putchar((n % 10) + '0');
    return (len);
}
