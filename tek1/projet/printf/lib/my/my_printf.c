/*
** EPITECH PROJECT, 2026
** my_printf.c
** File description:
** Main function
*/

#include "my.h"

static int check_floats(char arg, va_list list, int prec)
{
    if (arg == 'f' || arg == 'F')
        return (my_put_float(va_arg(list, double), prec, arg));
    if (arg == 'e' || arg == 'E')
        return (my_put_e(va_arg(list, double), prec, arg));
    if (arg == 'g' || arg == 'G')
        return (my_put_float(va_arg(list, double), prec, 'g'));
    if (arg == 'b')
        return (my_put_binary(va_arg(list, unsigned int)));
    if (arg == '%')
        return (my_putchar('%'));
    return (0);
}

static int check(char arg, va_list list, int prec)
{
    if (arg == 'd' || arg == 'i')
        return (my_put_nbr(va_arg(list, int)));
    if (arg == 's')
        return (print_with_precision_str(va_arg(list, char *), prec));
    if (arg == 'c')
        return (my_putchar((char)va_arg(list, int)));
    if (arg == 'u')
        return (my_put_unsigned(va_arg(list, unsigned int)));
    if (arg == 'x')
        return (my_put_hex_lower(va_arg(list, unsigned int)));
    if (arg == 'X')
        return (my_put_hex_upper(va_arg(list, unsigned int)));
    if (arg == 'o')
        return (my_put_octal(va_arg(list, unsigned int)));
    if (arg == 'p')
        return (my_put_pointer(va_arg(list, void *)));
    return (check_floats(arg, list, prec));
}

static void parse_width_prec(const char *format, int *i, int *width, int *prec)
{
    if (format[*i] >= '0' && format[*i] <= '9')
        *width = get_nb(format, i);
    if (format[*i] == '.') {
        *i = *i + 1;
        *prec = get_nb(format, i);
    }
}

static int handle_specifiers(const char *format, int *i, va_list list)
{
    int width = 0;
    int prec = -1;
    int flags[3] = {0, 0, 0};
    int c = 0;

    handle_flags(format, i, flags);
    parse_width_prec(format, i, &width, &prec);
    if (format[*i] == 'l') {
        *i = *i + 1;
        return (my_put_long(va_arg(list, long)));
    }
    c = c + handle_extra(format, i, flags);
    if (flags[2] != '-')
        c = c + handle_width(width, 1);
    c = c + check(format[*i], list, prec);
    if (flags[2] == '-')
        c = c + handle_width(width, 1);
    return (c);
}

int my_printf(const char *format, ...)
{
    va_list list;
    int count = 0;
    int i = 0;

    va_start(list, format);
    while (format[i]) {
        if (format[i] == '%') {
            i = i + 1;
            count = count + handle_specifiers(format, &i, list);
        } else {
            count = count + my_putchar(format[i]);
        }
        if (format[i])
            i = i + 1;
    }
    va_end(list);
    return (count);
}
