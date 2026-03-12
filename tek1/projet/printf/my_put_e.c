/*
** EPITECH PROJECT, 2026
** my_put_e.c
** File description:
** handles %e
*/

#include "my.h"

int my_put_e(double nb, int precision, char type)
{
    int count = 0;
    int exp = 0;

    if (nb == 0) {
        count = my_put_float(0, precision, 'f');
        return (count + my_putstr(type == 'e' ? "e+00" : "E+00"));
    }
    for (; nb >= 10 || nb <= -10; exp++)
        nb /= 10;
    for (; nb < 1 && nb > -1 && nb != 0; exp--)
        nb *= 10;
    count = my_put_float(nb, precision, 'f');
    count += my_putchar(type);
    count += (exp >= 0 ? my_putchar('+') : my_putchar('-'));
    exp = (exp < 0) ? -exp : exp;
    if (exp < 10)
        count += my_putchar('0');
    return (count + my_put_nbr(exp));
}
