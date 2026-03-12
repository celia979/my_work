/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** main
*/

#include "my.h"

static int print_error(void)
{
    write(2, "Error\n", 6);
    return 84;
}

static int handle_file_mode(char const *filepath)
{
    char **map = NULL;
    map_info_t info;

    if (load_map_from_file(filepath, &map, &info) == -1)
        return print_error();
    if (solve_map(map, &info) == -1) {
        free_map(map, info.rows);
        return print_error();
    }
    print_map(map, info.rows, info.cols);
    free_map(map, info.rows);
    return 0;
}

static int handle_generator_mode(int size, char const *pattern)
{
    char **map = NULL;
    map_info_t info;

    if (size <= 0)
        return print_error();
    if (generate_map(size, pattern, &map, &info) == -1)
        return print_error();
    if (solve_map(map, &info) == -1) {
        free_map(map, info.rows);
        return print_error();
    }
    print_map(map, info.rows, info.cols);
    free_map(map, info.rows);
    return 0;
}

int main(int argc, char **argv)
{
    int size = 0;

    if (argc == 2)
        return handle_file_mode(argv[1]);
    if (argc == 3) {
        size = my_getnbr(argv[1]);
        return handle_generator_mode(size, argv[2]);
    }
    return print_error();
}
