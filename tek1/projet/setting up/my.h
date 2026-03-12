/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>

typedef struct map_info_s {
    int rows;
    int cols;
} map_info_t;

typedef struct square_s {
    int row;
    int col;
    int size;
} square_t;

typedef struct char_pos_s {
    int line;
    int col;
    int max_cols;
} char_pos_t;

typedef struct check_params_s {
    char **map;
    map_info_t *info;
    square_t *best;
} check_params_t;

typedef struct square_params_s {
    char **map;
    int row;
    int col;
    int size;
} square_params_t;

typedef struct square_check_s {
    char **map;
    int row;
    int col;
    int size;
    map_info_t *info;
} square_check_t;

int load_map_from_file(char const *filepath, char ***map, map_info_t *info);
int generate_map(int size, char const *pattern, char ***map, map_info_t *info);
int solve_map(char **map, map_info_t *info);
void print_map(char **map, int rows, int cols);
void free_map(char **map, int rows);
int my_getnbr(char const *str);
int my_strlen(char const *str);
char *my_strdup(char const *str);
int is_valid_square(square_params_t *params, map_info_t *info);
square_t find_largest_square(char **map, map_info_t *info);
int parse_first_line(char const *content, int *rows);
int count_columns(char const *content, int start);
int parse_map_dimensions(char const *content, map_info_t *info);
int allocate_map_rows(char ***map, map_info_t *info);

#endif
