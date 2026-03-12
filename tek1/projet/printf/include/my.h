/*
** EPITECH PROJECT, 2026
** my_printf
** File description:
** Header file
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdarg.h>

void handle_flags(const char *format, int *i, int *flags);
int handle_extra(const char *format, int *i, int *flags);

int my_printf(char const *format, ...);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_strlen(char const *str);
int my_putstr(char const *str);
int my_put_float(double nb, int precision, char type);
int my_put_e(double nb, int precision, char type);
int my_put_g(double nb, int precision, char type);
int my_put_long(long nb);
int my_put_binary(unsigned int nb);
int my_put_hex_lower(unsigned int nb);
int my_put_hex_upper(unsigned int nb);
int my_put_octal(unsigned int nb);
int my_put_unsigned(unsigned int nb);
int my_put_pointer(void *ptr);
int get_nb_len(long nb);
int handle_width(int width, int current_len);
int get_nb(const char *format, int *i);
int print_with_precision_str(char *str, int precision);

#endif
