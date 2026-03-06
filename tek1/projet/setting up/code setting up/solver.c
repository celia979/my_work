/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** trouve le plus grand carre
*/

#include "my.h"

static int check_row(char **map, int row, int col, int size)
{
    int j = 0;

    for (j = col; j < col + size; j++) {
        if (map[row][j] == 'o')
            return 0;
    }
    return 1;
}

int is_valid_square(char **map, int row, int col, int size, map_info_t *info)
{
    int i = 0;

    if (row + size > info->rows || col + size > info->cols)
        return 0;
    for (i = row; i < row + size; i++) {
        if (check_row(map, i, col, size) == 0)
            return 0;
    }
    return 1;
}

static int find_max_square_at_position(char **map, int row,
    int col, map_info_t *info)
{
    int size = 1;

    while (is_valid_square(map, row, col, size, info))
        size++;
    return size - 1;
}

static void update_best_square(square_t *best, square_t *current)
{
    if (current->size > best->size)
        *best = *current;
}

static void check_position(char **map, map_info_t *info, int row,
    int col, square_t *best)
{
    square_t current = {0, 0, 0};

    if (map[row][col] != '.')
        return;
    current.size = find_max_square_at_position(map, row, col, info);
    current.row = row;
    current.col = col;
    update_best_square(best, &current);
}

square_t find_largest_square(char **map, map_info_t *info)
{
    square_t best = {0, 0, 0};
    int row = 0;
    int col = 0;

    for (row = 0; row < info->rows; row++) {
        for (col = 0; col < info->cols; col++)
            check_position(map, info, row, col, &best);
    }
    return best;
}

static void place_square_row(char **map, int row, int col_start, int col_end)
{
    int j = 0;

    for (j = col_start; j < col_end; j++)
        map[row][j] = 'x';
}

static void place_square(char **map, square_t square)
{
    int i = 0;

    for (i = square.row; i < square.row + square.size; i++)
        place_square_row(map, i, square.col, square.col + square.size);
}

int solve_map(char **map, map_info_t *info)
{
    square_t largest = {0, 0, 0};

    if (map == NULL || info == NULL)
        return -1;
    largest = find_largest_square(map, info);
    if (largest.size > 0)
        place_square(map, largest);
    return 0;
}
