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

static int process_char(char **map, char const *content, int *idx,
    char_pos_t *pos)
{
    if (content[*idx] != '.' && content[*idx] != 'o')
        return -1;
    if (pos->col >= pos->max_cols)
        return -1;
    map[pos->line][pos->col] = content[*idx];
    (*idx)++;
    return 0;
}

static int validate_line(char **map, char const *content, int *idx,
    char_pos_t *pos)
{
    pos->col = 0;
    while (content[*idx] != '\0' && content[*idx] != '\n') {
        if (process_char(map, content, idx, pos) == -1)
            return -1;
        pos->col++;
    }
    if (pos->col != pos->max_cols)
        return -1;
    if (content[*idx] == '\n')
        (*idx)++;
    map[pos->line][pos->col] = '\0';
    return 0;
}

static int validate_and_fill_map(char **map, char const *content,
    int start, map_info_t *info)
{
    char_pos_t pos;
    int idx = start;

    pos.line = 0;
    pos.max_cols = info->cols;
    while (pos.line < info->rows) {
        if (validate_line(map, content, &idx, &pos) == -1)
            return -1;
        pos.line++;
    }
    return 0;
}

int allocate_map_rows(char ***map, map_info_t *info)
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

static int load_and_parse(char const *filepath, char **content,
    map_info_t *info)
{
    int file_size = get_file_size(filepath);
    int start = 0;

    if (file_size == -1)
        return -1;
    *content = read_file_content(filepath, file_size);
    if (*content == NULL)
        return -1;
    start = parse_map_dimensions(*content, info);
    if (start == -1) {
        free(*content);
        return -1;
    }
    return start;
}

int load_map_from_file(char const *filepath, char ***map, map_info_t *info)
{
    char *content = NULL;
    int start = 0;

    start = load_and_parse(filepath, &content, info);
    if (start == -1)
        return -1;
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
