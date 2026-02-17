/*
** EPITECH PROJECT, 2025
** my_strcat.c
** File description:
** yes
*/

#include <stdio.h>
#include <unistd.h>
#include "../../include/my.h"

char *my_strcat(char *d, char const *c)
{
    char *dest = "hello";
    char *src = "world";
    int length;
    int l = 0;

    length = 0;
    while (dest[length] != '\0')
        length++;
    for (l = 0; src[l] != '\0'; l++)
        dest[(length)] = src[l];
    dest[length] = '\0';
    my_putstr(dest);
    return 0;
}
