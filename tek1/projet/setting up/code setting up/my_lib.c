/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** fonction que j'ai bessoin
*/

#include "my.h"

int my_strlen(char const *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int my_getnbr(char const *str)
{
    int result = 0;
    int i = 0;
    int sign = 1;

    if (str == NULL)
        return 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *dup = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (dup == NULL)
        return NULL;
    for (i = 0; i < len; i++)
        dup[i] = str[i];
    dup[i] = '\0';
    return dup;
}

void print_map(char **map, int rows, int cols)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            write(1, &map[i][j], 1);
        write(1, "\n", 1);
    }
}

void free_map(char **map, int rows)
{
    int i = 0;

    if (map == NULL)
        return;
    for (i = 0; i < rows; i++) {
        if (map[i] != NULL)
            free(map[i]);
    }
    free(map);
}
