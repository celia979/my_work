/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** yes
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        my_putchar(nb);
    }
    if (nb > 0)
        my_putchar(nb);
    if (nb == 0)
        my_putchar('0');
    return 0;
}
