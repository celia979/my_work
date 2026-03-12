/*
** EPITECH PROJECT, 2026
** my_strndup
** File description:
** Duplicate a string at a char
*/

#include <my.h>

char *my_strndup(char *src, char separator)
{
    char *temp = NULL;
    int len = 0;

    while (src[len] && src[len] != separator && src[len] != '\n')
        len++;
    temp = malloc(sizeof(char) * (len + 1));
    if (!temp)
        return NULL;
    for (int i = 0; i < len; i++)
        temp[i] = src[i];
    temp[len] = '\0';
    return temp;
}
