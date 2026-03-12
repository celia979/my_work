/*
** EPITECH PROJECT, 2026
** my_put_g.c
** File description:
** handles %g
*/

#include "my.h"

int my_put_g(double nb, int precision, char type)
{
    double temp = (nb < 0) ? -nb : nb;
    char f_t = (type == 'g') ? 'f' : 'F';
    char e_t = (type == 'g') ? 'e' : 'E';

    if (temp >= 1000000 || (temp < 0.0001 && temp != 0)) {
        return (my_put_e(nb, precision, e_t));
    }
    return (my_put_float(nb, precision, f_t));
}
