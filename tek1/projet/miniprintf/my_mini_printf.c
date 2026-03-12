/*
** EPITECH PROJECT, 2025
** my_mini_printf.c
** File description:
** yes
*/

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

static int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

static char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    my_putchar(i);
    return 0;
}

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i = i + 1;
    }
    return 0;
}

static int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar((str[i]));
        i = i + 1;
    }
    return 0;
}

int my_put_nbr(int nb)
{
    long value = nb;
    long div = 1;
    char digit;

    while (value / div >= 10)
        div = div * 10;
    while (div > 0) {
        digit = (value / div) % 10 + '0';
        div = div / 10;
    }
    return 0;
}

int check(char arg, va_list list)
{
    if (arg == 'i' || arg == 'd')
        my_put_nbr(va_arg(list, int));
    if (arg == 's')
        my_putstr(va_arg(list, char*));
    if (arg == 'c')
        my_putchar(va_arg(list, int));
    if (arg == '%')
        my_putchar('%');
    return 0;
}

int my_mini_printf(const char *format, ...)
{
    va_list list;
    int i = 0;
    int count = 0;

    va_start(list, format);
    if (!format)
        return -1;
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            count += check(format[i + 1], list);
            i++;
        } else {
            count += my_putchar(format[i]);
        }
    }
    va_end(list);
    return 0;
}
