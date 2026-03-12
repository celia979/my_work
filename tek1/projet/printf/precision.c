/*
** EPITECH PROJECT, 2025
** precison.c
** File description:
** precision
*/

#include "my.h"

static int print_precision_zeros(int precision, int len)
{
    int i = 0;
    int count = 0;

    while (i < precision - len) {
        my_putchar('0');
        i = i + 1;
        count = count + 1;
    }
    return (count);
}

int print_with_precision_int(int nb, int precision)
{
    int count = 0;
    int len = get_nb_len(nb);
    long n = nb;

    if (n < 0) {
        count = count + my_putchar('-');
        n = -n;
        len = len - 1;
    }
    count = count + print_precision_zeros(precision, len);
    count = count + my_put_nbr(n);
    return (count);
}

int print_with_precision_str(char *str, int precision)
{
    int i = 0;
    int count = 0;

    if (str == 0)
        return (my_putstr("(null)"));
    if (precision < 0)
        return (my_putstr(str));
    while (str[i] != '\0' && i < precision) {
        my_putchar(str[i]);
        i = i + 1;
        count = count + 1;
    }
    return (count);
}

int print_width_spaces(int width, int total_len)
{
    int i = 0;
    int count = 0;

    while (i < width - total_len) {
        my_putchar(' ');
        i = i + 1;
        count = count + 1;
    }
    return (count);
}
