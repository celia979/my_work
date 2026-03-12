/*
** EPITECH PROJECT, 2026
** my.h
** File description:
** Include of Lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#ifndef MY
    #define MY

int mini_printf(const char *format, ...);
int my_getnbr(char *str);
int my_put_nbr(int nb);
void my_putchar(char c);
int my_putstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strlen(char const *str);
char *my_strndup(char *src, char separator);

#endif /* MY */
