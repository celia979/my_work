/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Line parsing into argument array
*/

#include "../include/mysh.h"

static int count_tokens(char const *line)
{
    char *tmp = my_strdup(line);
    char *token = NULL;
    int count = 0;

    if (!tmp)
        return 0;
    token = strtok(tmp, " \t");
    while (token) {
        count++;
        token = strtok(NULL, " \t");
    }
    free(tmp);
    return count;
}

static void free_partial(char **args, int filled, char *tmp)
{
    int i = 0;

    while (i < filled) {
        free(args[i]);
        i++;
    }
    free(args);
    free(tmp);
}

static int tokenize(char **args, char *tmp, int count)
{
    char *token = strtok(tmp, " \t");
    int i = 0;

    while (token && i < count) {
        args[i] = my_strdup(token);
        if (!args[i])
            return i;
        i++;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;
    return -1;
}

static char **fill_args(char const *line, int count)
{
    char **args = malloc(sizeof(char *) * (count + 1));
    char *tmp = my_strdup(line);
    int err = 0;

    if (!args || !tmp) {
        free(args);
        free(tmp);
        return NULL;
    }
    err = tokenize(args, tmp, count);
    if (err != -1) {
        free_partial(args, err, tmp);
        return NULL;
    }
    free(tmp);
    return args;
}

char **split_args(char const *line)
{
    int count = count_tokens(line);

    if (count == 0)
        return NULL;
    return fill_args(line, count);
}

void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;
    while (args[i]) {
        free(args[i]);
        i++;
    }
    free(args);
}
