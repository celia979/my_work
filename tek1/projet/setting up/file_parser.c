/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** parsing file
*/

#include "my.h"

int parse_first_line(char const *content, int *rows)
{
    int i = 0;
    int nbr = 0;

    while (content[i] != '\0' && content[i] != '\n') {
        if (content[i] < '0' || content[i] > '9')
            return -1;
        nbr = nbr * 10 + (content[i] - '0');
        i++;
    }
    if (content[i] != '\n' || nbr <= 0)
        return -1;
    *rows = nbr;
    return i + 1;
}

int count_columns(char const *content, int start)
{
    int cols = 0;

    while (content[start + cols] != '\0' && content[start + cols] != '\n')
        cols++;
    return cols;
}

int parse_map_dimensions(char const *content, map_info_t *info)
{
    int start = 0;

    start = parse_first_line(content, &info->rows);
    if (start == -1)
        return -1;
    info->cols = count_columns(content, start);
    return start;
}
