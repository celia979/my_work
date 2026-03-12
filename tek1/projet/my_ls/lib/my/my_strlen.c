/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Get string length
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i = i + 1;
    return i;
}
