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

int load_map_from_file(char const *filepath, char ***map, map_info_t *info);
int generate_map(int size, char const *pattern, char ***map, map_info_t *info);
int solve_map(char **map, map_info_t *info);
void print_map(char **map, int rows, int cols);
void free_map(char **map, int rows);
int my_getnbr(char const *str);
int my_strlen(char const *str);
char *my_strdup(char const *str);
int is_valid_square(char **map, int row, int col, int size, map_info_t *info);
square_t find_largest_square(char **map, map_info_t *info);

#endif
