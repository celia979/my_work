/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** trouve le plus grand carre
*/

#include "my.h"

static int check_row(square_check_t *check, int current_row)
{
    int j = 0;

    for (j = check->col; j < check->col + check->size; j++) {
        if (check->map[current_row][j] == 'o')
            return 0;
    }
    return 1;
}

int is_valid_square(square_params_t *params, map_info_t *info)
{
    square_check_t check;
    int i = 0;

    if (params->row + params->size > info->rows)
        return 0;
    if (params->col + params->size > info->cols)
        return 0;
    check.map = params->map;
    check.row = params->row;
    check.col = params->col;
    check.size = params->size;
    check.info = info;
    for (i = params->row; i < params->row + params->size; i++) {
        if (check_row(&check, i) == 0)
            return 0;
    }
    return 1;
}

static int find_max_square_at_position(check_params_t *params, int row,
    int col)
{
    square_params_t sp;
    int size = 1;

    sp.map = params->map;
    sp.row = row;
    sp.col = col;
    sp.size = size;
    while (is_valid_square(&sp, params->info)) {
        size++;
        sp.size = size;
    }
    return size - 1;
}

static void update_best_square(square_t *best, square_t *current)
{
    if (current->size > best->size)
        *best = *current;
}

static void check_position(check_params_t *params, int row, int col)
{
    square_t current = {0, 0, 0};

    if (params->map[row][col] != '.')
        return;
    current.size = find_max_square_at_position(params, row, col);
    current.row = row;
    current.col = col;
    update_best_square(params->best, &current);
}

square_t find_largest_square(char **map, map_info_t *info)
{
    check_params_t params;
    square_t best = {0, 0, 0};
    int row = 0;
    int col = 0;

    params.map = map;
    params.info = info;
    params.best = &best;
    for (row = 0; row < info->rows; row++) {
        for (col = 0; col < info->cols; col++)
            check_position(&params, row, col);
    }
    return best;
}

static void place_square_row(char **map, int row, int col_start, int col_end)
{
    int j = 0;

    for (j = col_start; j < col_end; j++)
        map[row][j] = 'x';
}

static void place_square(char **map, square_t *square)
{
    int i = 0;

    for (i = square->row; i < square->row + square->size; i++)
        place_square_row(map, i, square->col, square->col + square->size);
}

int solve_map(char **map, map_info_t *info)
{
    square_t largest = {0, 0, 0};

    if (map == NULL || info == NULL)
        return -1;
    largest = find_largest_square(map, info);
    if (largest.size > 0)
        place_square(map, &largest);
    return 0;
}
