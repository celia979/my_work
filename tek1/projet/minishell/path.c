/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Binary path resolution using PATH env variable
*/

#include "mysh.h"

static char *get_path_env(char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i] + 5;
        i++;
    }
    return NULL;
}

static char *build_full_path(char *dir, char *cmd)
{
    return my_strjoin(dir, cmd, '/');
}

static char *search_in_path(char *path_val, char *cmd)
{
    char *path_copy = my_strdup(path_val);
    char *dir = NULL;
    char *full = NULL;
    char *saveptr = NULL;

    if (path_copy == NULL)
        return NULL;
    dir = strtok_r(path_copy, ":", &saveptr);
    while (dir != NULL) {
        full = build_full_path(dir, cmd);
        if (full != NULL && access(full, X_OK) == 0) {
            free(path_copy);
            return full;
        }
        free(full);
        full = NULL;
        dir = strtok_r(NULL, ":", &saveptr);
    }
    free(path_copy);
    return NULL;
}

char *find_binary(char *cmd, char **env)
{
    char *path_val = NULL;

    if (cmd[0] == '/' || cmd[0] == '.') {
        if (access(cmd, X_OK) == 0)
            return my_strdup(cmd);
        return NULL;
    }
    path_val = get_path_env(env);
    if (path_val == NULL)
        return NULL;
    return search_in_path(path_val, cmd);
}
