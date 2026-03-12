/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** file parser for radar script
*/

#include "./my.h"

int count_lines(char const *filepath, char type)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int count = 0;

    if (!file)
        return -1;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[0] == type)
            count++;
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return count;
}

static int process_airplane_line(char *line, script_data_t *script, int *index)
{
    if (line[0] != 'A')
        return 0;
    if (parse_airplane_line(line, &script->airplanes[*index]) == 84)
        return 84;
    (*index)++;
    return 0;
}

static int read_airplanes(char const *filepath, script_data_t *script)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int index = 0;

    if (!file)
        return 84;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (process_airplane_line(line, script, &index) == 84) {
            free(line);
            fclose(file);
            return 84;
        }
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}

static int process_tower_line(char *line, script_data_t *script, int *index)
{
    if (line[0] != 'T')
        return 0;
    if (parse_tower_line(line, &script->towers[*index]) == 84)
        return 84;
    (*index)++;
    return 0;
}

static int read_towers(char const *filepath, script_data_t *script)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int index = 0;

    if (!file)
        return 84;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (process_tower_line(line, script, &index) == 84) {
            free(line);
            fclose(file);
            return 84;
        }
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}

int allocate_script_data(script_data_t *script)
{
    script->airplanes = malloc(sizeof(plane_data_t) * script->airplane_count);
    if (!script->airplanes)
        return 84;
    script->towers = malloc(sizeof(tower_data_t) * script->tower_count);
    if (!script->towers) {
        free(script->airplanes);
        return 84;
    }
    return 0;
}

int validate_counts(script_data_t *script)
{
    if (script->airplane_count <= 0)
        return 84;
    if (script->tower_count <= 0)
        return 84;
    return 0;
}

int read_script_content(char const *filepath, script_data_t *script)
{
    if (read_airplanes(filepath, script) == 84)
        return 84;
    if (read_towers(filepath, script) == 84)
        return 84;
    return 0;
}
