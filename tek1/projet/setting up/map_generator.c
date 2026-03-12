/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** map generator
*/

#include "my.h"

static int allocate_map(char ***map, int size)
{
    int i = 0;

    *map = malloc(sizeof(char *) * size);
    if (*map == NULL)
        return -1;
    for (i = 0; i < size; i++) {
        (*map)[i] = malloc(sizeof(char) * (size + 1));
        if ((*map)[i] == NULL) {
            free_map(*map, i);
            return -1;
        }
        (*map)[i][size] = '\0';
    }
    return 0;
}

static void fill_map_row(char **map, int row, int size, char const *pattern)
{
    int col = 0;
    int pattern_idx = 0;
    int pattern_len = my_strlen(pattern);

    for (col = 0; col < size; col++) {
        pattern_idx = (row * size + col) % pattern_len;
        map[row][col] = pattern[pattern_idx];
    }
}

static void fill_map_with_pattern(char **map, int size, char const *pattern)
{
    int row = 0;

    for (row = 0; row < size; row++)
        fill_map_row(map, row, size, pattern);
}

int generate_map(int size, char const *pattern, char ***map, map_info_t *info)
{
    if (size <= 0 || pattern == NULL)
        return -1;
    if (my_strlen(pattern) == 0)
        return -1;
    if (allocate_map(map, size) == -1)
        return -1;
    info->rows = size;
    info->cols = size;
    fill_map_with_pattern(*map, size, pattern);
    return 0;
}
