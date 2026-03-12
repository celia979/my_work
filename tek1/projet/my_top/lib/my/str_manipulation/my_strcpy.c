/*
** EPITECH PROJECT, 2026
** my_strcpy
** File description:
** copy an str
*/

#include <stdarg.h>
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int j = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
        j = j + 1;
    }
    dest[j] = '\0';
    return dest;
}
