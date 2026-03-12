/*
** EPITECH PROJECT, 2025
** mini printf
** File description:
** refaire ~~ un printf
*/

#include "my.h"

void static mini_putchar(char c)
{
    write(1, &c, 1);
}

int static mini_putstr(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len += 1;
    write(1, str, len);
    return len;
}

int mini_put_nbr(int nb)
{
    long value = 0;
    long ABS_nb = 0;
    int nb_nb = 0;

    if (-2147483648 >= nb || nb >= 2147483647)
        return 0;
    if (nb < 0) {
        ABS_nb = nb;
        ABS_nb = -ABS_nb;
        mini_putchar('-');
        nb_nb += 1;
    } else
        ABS_nb = nb;
    value = ABS_nb % 10;
    if (ABS_nb != value)
        nb_nb += mini_put_nbr((ABS_nb - value) / 10);
    mini_putchar(value + 48);
    return nb_nb + 1;
}

int len_to_before(const char *str, int start, char stopper)
{
    int letter = start;

    while ((str[letter] != stopper) && (str[letter] != '\0'))
        letter += 1;
    return letter - start;
}

int good_print(char letter, va_list arg)
{
    switch (letter) {
        case 'd':
            return mini_put_nbr(va_arg(arg, int));
        case 'i':
            return mini_put_nbr(va_arg(arg, int));
        case 's':
            return mini_putstr(va_arg(arg, char *));
        case 'c':
            mini_putchar(va_arg(arg, int));
            return 1;
        case '%':
            mini_putchar('%');
            return 1;
    }
    return 0;
}

int print(const char *format, ...)
{
    int letter = 0;
    int nb_char = 0;
    va_list arg;

    if (format == NULL)
        return -1;
    va_start(arg, format);
    while (format[letter] != '\0') {
        write(1, &format[letter], len_to_before(format, letter, '%'));
        nb_char += len_to_before(format, letter, '%');
        letter += len_to_before(format, letter, '%');
        if (format[letter] != '\0')
            letter += 1;
        nb_char += good_print(format[letter], arg);
        if (format[letter] != '\0')
            letter += 1;
    }
    va_end(arg);
    return nb_char;
}
