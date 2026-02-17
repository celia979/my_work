/*
** EPITECH PROJECT, 2026
** B-CPE-210
** File description:
** Utility functions for character and string manipulation
*/

#include <unistd.h>
#include "my.h"

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1;
    }
    return 0;
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n') {
        return 1;
    }
    return 0;
}
