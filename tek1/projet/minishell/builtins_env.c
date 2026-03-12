/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** setenv and unsetenv built-in commands
*/

#include "mysh.h"

int builtin_setenv(char **args, shell_t *shell)
{
    if (!args[1]) {
        write(2, "setenv: Too few arguments\n", 26);
        return 1;
    }
    if (!args[2])
        return set_env_value(&shell->env, args[1], "");
    return set_env_value(&shell->env, args[1], args[2]);
}

int builtin_unsetenv(char **args, shell_t *shell)
{
    if (!args[1]) {
        write(2, "unsetenv: Too few arguments\n", 28);
        return 1;
    }
    return unset_env_value(&shell->env, args[1]);
}

char *build_entry(env_t *cur)
{
    char *entry = malloc(strlen(cur->key) + strlen(cur->value) + 2);

    if (!entry)
        return NULL;
    my_strcpy(entry, cur->key);
    my_strcat(entry, "=");
    my_strcat(entry, cur->value);
    return entry;
}
