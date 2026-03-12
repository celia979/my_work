/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Compare two strings
*/

#include "../../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}
