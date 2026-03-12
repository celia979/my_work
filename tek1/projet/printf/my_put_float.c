/*
** EPITECH PROJECT, 2026
** my_put_f.c
** File description:
** handles %f
*/

#include "my.h"

static int print_dec(double dec, int prec, int is_g)
{
    int c = 0;
    char s[15];
    int last = 0;

    for (int i = 0; i < prec; i = i + 1) {
        dec *= 10;
        s[i] = (int)dec + '0';
        dec -= (int)dec;
        if (s[i] != '0')
            last = i + 1;
    }
    if (is_g && last > 0)
        prec = last;
    else if (is_g && last == 0)
        prec = 0;
    for (int i = 0; i < prec; i = i + 1)
        c += my_putchar(s[i]);
    return (c);
}

int my_put_float(double nb, int prec, char type)
{
    int c = 0;
    double off = 0.5;
    long ent;

    if (prec < 0)
        prec = 6;
    for (int i = 0; i < prec; i = i + 1)
        off /= 10.0;
    nb += (nb < 0) ? -off : off;
    ent = (long)nb;
    if (nb < 0 && ent == 0)
        c += my_putchar('-');
    c += my_put_nbr(ent);
    if (prec > 0 || (type != 'g' && type != 'G')) {
        c += my_putchar('.');
        nb = (nb < 0) ? -(nb - (double)ent) : (nb - (double)ent);
        c += print_dec(nb, prec, (type == 'g' || type == 'G'));
    }
    return (c);
}
