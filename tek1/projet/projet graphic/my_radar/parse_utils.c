/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** parser utilities
*/

#include "./my.h"

void skip_spaces(char *str, int *i)
{
    while (str[*i] == ' ' || str[*i] == '\t')
        (*i)++;
}

static float parse_decimal_part(char *str, int *i)
{
    float decimal = 0.1f;
    float result = 0.0f;

    while (str[*i] >= '0' && str[*i] <= '9') {
        result += (str[*i] - '0') * decimal;
        decimal *= 0.1f;
        (*i)++;
    }
    return result;
}

float parse_float(char *str, int *i)
{
    float result = 0.0f;
    float sign = 1.0f;

    if (str[*i] == '-') {
        sign = -1.0f;
        (*i)++;
    }
    while (str[*i] >= '0' && str[*i] <= '9') {
        result = result * 10.0f + (str[*i] - '0');
        (*i)++;
    }
    if (str[*i] == '.') {
        (*i)++;
        result += parse_decimal_part(str, i);
    }
    return result * sign;
}

int parse_int(char *str, int *i)
{
    int result = 0;
    int sign = 1;

    if (str[*i] == '-') {
        sign = -1;
        (*i)++;
    }
    while (str[*i] >= '0' && str[*i] <= '9') {
        result = result * 10 + (str[*i] - '0');
        (*i)++;
    }
    return result * sign;
}

static void parse_airplane_coords(char *line, plane_data_t *data, int *i)
{
    skip_spaces(line, i);
    data->start_x = parse_float(line, i);
    skip_spaces(line, i);
    data->start_y = parse_float(line, i);
    skip_spaces(line, i);
    data->end_x = parse_float(line, i);
    skip_spaces(line, i);
    data->end_y = parse_float(line, i);
}

int parse_airplane_line(char *line, plane_data_t *data)
{
    int i = 2;

    parse_airplane_coords(line, data, &i);
    skip_spaces(line, &i);
    data->delay = parse_int(line, &i);
    skip_spaces(line, &i);
    data->id = parse_int(line, &i);
    return 0;
}

int parse_tower_line(char *line, tower_data_t *data)
{
    int i = 2;

    skip_spaces(line, &i);
    data->x = parse_float(line, &i);
    skip_spaces(line, &i);
    data->y = parse_float(line, &i);
    skip_spaces(line, &i);
    data->id = parse_int(line, &i);
    data->radius = 150.0f;
    return 0;
}
