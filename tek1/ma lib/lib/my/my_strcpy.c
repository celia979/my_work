/*
** EPITECH PROJECT, 2025
** my_strcpy.c
** File description:
** yes
*/

#include <unistd.h>
#include "../../include/my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    my_putchar(i);
    return 0;
}
