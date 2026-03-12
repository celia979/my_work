/*
** EPITECH PROJECT, 2025
** flag.c
** File description:
** flags
*/

#include <unistd.h>
#include "my.h"

void handle_flags(const char *format, int *i, int *flags)
{
    while (format[*i] == '+' || format[*i] == '#' ||
        format[*i] == '-' || format[*i] == ' ' || format[*i] == '0') {
        if (format[*i] == '+')
            flags[0] = 1;
        if (format[*i] == '#')
            flags[1] = 1;
        if (format[*i] == '-')
            flags[2] = '-';
        if (format[*i] == ' ' && flags[2] != '-')
            flags[2] = ' ';
        *i = *i + 1;
    }
}

int handle_extra(const char *format, int *i, int *flags)
{
    int count = 0;

    if (flags[0] && (format[*i] == 'd' || format[*i] == 'i'))
        count = count + my_putchar('+');
    else if (flags[2] == ' ' && (format[*i] == 'd' || format[*i] == 'i'))
        count = count + my_putchar(' ');
    if (flags[1] && format[*i] == 'x')
        count = count + my_putstr("0x");
    if (flags[1] && format[*i] == 'o')
        count = count + my_putchar('0');
    return (count);
}
