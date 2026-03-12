/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Custom string utility functions
*/

#include "mysh.h"

int my_strlen(char const *s)
{
    int i = 0;

    while (s[i])
        i++;
    return i;
}

char *my_strdup(char const *s)
{
    int len = my_strlen(s);
    char *dup = malloc(len + 1);
    int i = 0;

    if (!dup)
        return NULL;
    while (i < len) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char *my_strjoin(char const *s1, char const *s2, char sep)
{
    int l1 = my_strlen(s1);
    int l2 = my_strlen(s2);
    char *res = malloc(l1 + l2 + 2);

    if (!res)
        return NULL;
    my_strcpy(res, s1);
    res[l1] = sep;
    my_strcpy(res + l1 + 1, s2);
    return res;
}

int my_atoi(char const *s)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (s[i] == '-' || s[i] == '+') {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9') {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    return result * sign;
}

void my_strcat(char *dst, char const *src)
{
    int i = my_strlen(dst);
    int j = 0;

    while (src[j]) {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';
}
