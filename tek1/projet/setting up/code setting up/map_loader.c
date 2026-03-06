/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** load map from file
*/

#include "my.h"

static int get_file_size(char const *filepath)
{
    struct stat st;

    if (stat(filepath, &st) == -1)
        return -1;
    return st.st_size;
}

static char *read_file_content(char const *filepath, int size)
{
    int fd = open(filepath, O_RDONLY);
    char *content = NULL;
    int bytes_read = 0;

    if (fd == -1)
        return NULL;
    content = malloc(sizeof(char) * (size + 1));
    if (content == NULL) {
        close(fd);
        return NULL;
    }
    bytes_read = read(fd, content, size);
    close(fd);
    if (bytes_read == -1) {
        free(content);
        return NULL;
    }
    content[bytes_read] = '\0';
    return content;
}

static int parse_first_line(char const *content, int *rows)
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

static int count_columns(char const *content, int start)
{
    int cols = 0;

    while (content[start + cols] != '\0' && content[start + cols] != '\n')
        cols++;
    return cols;
}

static int validate_char(char c)
{
    if (c != '.' && c != 'o')
        return -1;
    return 0;
}

static int process_line_char(char **map, char const *content, int *idx,
    int line, int col, int max_cols)
{
    if (validate_char(content[*idx]) == -1)
        return -1;
    if (col >= max_cols)
        return -1;
    map[line][col] = content[*idx];
    (*idx)++;
    return 0;
}

static int validate_line(char **map, char const *content, int *idx,
    int line, map_info_t *info)
{
    int col = 0;

    while (content[*idx] != '\0' && content[*idx] != '\n') {
        if (process_line_char(map, content, idx, line, col, info->cols) == -1)
            return -1;
        col++;
    }
    if (col != info->cols)
        return -1;
    if (content[*idx] == '\n')
        (*idx)++;
    map[line][col] = '\0';
    return 0;
}

static int validate_and_fill_map(char **map, char const *content,
    int start, map_info_t *info)
{
    int line = 0;
    int idx = start;

    while (line < info->rows) {
        if (validate_line(map, content, &idx, line, info) == -1)
            return -1;
        line++;
    }
    return 0;
}

static int allocate_map_rows(char ***map, map_info_t *info)
{
    int i = 0;

    *map = malloc(sizeof(char *) * info->rows);
    if (*map == NULL)
        return -1;
    for (i = 0; i < info->rows; i++) {
        (*map)[i] = malloc(sizeof(char) * (info->cols + 1));
        if ((*map)[i] == NULL) {
            free_map(*map, i);
            return -1;
        }
    }
    return 0;
}

static int parse_map_dimensions(char const *content, map_info_t *info)
{
    int start = 0;

    start = parse_first_line(content, &info->rows);
    if (start == -1)
        return -1;
    info->cols = count_columns(content, start);
    return start;
}

int load_map_from_file(char const *filepath, char ***map, map_info_t *info)
{
    int file_size = get_file_size(filepath);
    char *content = NULL;
    int start = 0;

    if (file_size == -1)
        return -1;
    content = read_file_content(filepath, file_size);
    if (content == NULL)
        return -1;
    start = parse_map_dimensions(content, info);
    if (start == -1) {
        free(content);
        return -1;
    }
    if (allocate_map_rows(map, info) == -1) {
        free(content);
        return -1;
    }
    if (validate_and_fill_map(*map, content, start, info) == -1) {
        free_map(*map, info->rows);
        free(content);
        return -1;
    }
    free(content);
    return 0;
}
