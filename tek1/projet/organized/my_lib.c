/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** my_Lib
*/

#include "struct.h"
#include <unistd.h>
#include <stdlib.h>

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i = i + 1;
    }
    return i;
}

char *my_strdup(char *src)
{
    int i = 0;
    int len;
    char *dup = 0;

    if (src == 0)
        return (0);
    len = my_strlen(src);
    dup = malloc(sizeof(char) * (len + 1));
    if (dup == 0)
        return (0);
    while (src[i]) {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int my_put_nbr(int nb)
{
    char c;

    if (nb < 0) {
        write(1, "-", 1);
        nb = nb * -1;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    c = (nb % 10) + '0';
    write(1, &c, 1);
    return 0;
}

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i = i + 1;
    }
    return 0;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}
