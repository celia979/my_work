/*
** EPITECH PROJECT, 2026
** US Name Formatter
** File description:
** Main file for US Name Formatter program
*/

#include "my.h"
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int get_word_length(char const *str)
{
    int len = 0;

    while (str[len] != '\0' && !is_space(str[len]))
        len++;
    return len;
}
