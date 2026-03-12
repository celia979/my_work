/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get info in proc
*/

#include "my.h"

char *get_str_in_proc(char *what, char *where)
{
    char *file_path = my_strcat("/proc/", where);
    FILE *file = fopen(file_path, "r");
    char *value;
    char *line = "";
    size_t size = 0;
    int nread = getline(&line, &size, file);
    char *type = strtok(line, ": \t");

    while (nread != -1 && strcmp(type, what) != 0) {
        nread = getline(&line, &size, file);
        type = strtok(line, ": \t");
    }
    value = my_strdup(strtok(NULL, ": \t"));
    free(line);
    free(file_path);
    fclose(file);
    return value;
}

double get_value_in_proc(char *what, char *where)
{
    char *file_path = my_strcat("/proc/", where);
    FILE *file = fopen(file_path, "r");
    double value = 0;
    char *line = "";
    size_t size = 0;
    int nread = getline(&line, &size, file);
    char *type = strtok(line, ": \t");

    while (nread != -1 && strcmp(type, what) != 0) {
        nread = getline(&line, &size, file);
        type = strtok(line, ": \t");
    }
    value = strtod(strtok(NULL, ": \t"), 0);
    free(line);
    free(file_path);
    fclose(file);
    return value;
}
