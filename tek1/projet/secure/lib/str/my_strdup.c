/*
** EPITECH PROJECT, 2026
** my_strcmp
** File description:
** trouver la diff entre 2 str
*/

#include "my_str.h"

char *my_strdup(const char *str)
{
    int size = my_strlen(str);
    char *n_str = malloc(sizeof(char) * (size + 1));

    if (n_str == NULL)
        return NULL;
    for (int i = 0; i < size; i++) {
        n_str[i] = str[i];
    }
    n_str[size] = '\0';
    return n_str;
}
