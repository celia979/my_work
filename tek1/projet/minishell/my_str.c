/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Custom string utility functions
*/

#include "mysh.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return 0;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

char *my_strndup(char const *s, int n)
{
    char *dup = malloc(n + 1);
    int i = 0;

    if (!dup)
        return NULL;
    while (i < n && s[i]) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char *my_strchr(char const *s, char c)
{
    int i = 0;

    while (s[i]) {
        if (s[i] == c)
            return (char *)&s[i];
        i++;
    }
    return NULL;
}

void my_strcpy(char *dst, char const *src)
{
    int i = 0;

    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}
