/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Built-in dispatch table
*/

#include "mysh.h"

int is_builtin(char const *cmd)
{
    char const *builtins[] = {
        "cd", "setenv", "unsetenv", "env", "exit", NULL
    };
    int i = 0;

    while (builtins[i]) {
        if (my_strcmp(builtins[i], cmd) == 0)
            return 1;
        i++;
    }
    return 0;
}

static int try_cd(char **args, shell_t *shell, char const *cmd)
{
    if (my_strcmp(cmd, "cd") == 0)
        return builtin_cd(args, shell);
    return -1;
}

static int try_env_cmds(char **args, shell_t *shell, char const *cmd)
{
    if (my_strcmp(cmd, "setenv") == 0)
        return builtin_setenv(args, shell);
    if (my_strcmp(cmd, "unsetenv") == 0)
        return builtin_unsetenv(args, shell);
    if (my_strcmp(cmd, "env") == 0)
        return builtin_env(args, shell);
    if (my_strcmp(cmd, "exit") == 0)
        return builtin_exit(args, shell);
    return -1;
}

int exec_builtin(char **args, shell_t *shell)
{
    int ret = try_cd(args, shell, args[0]);

    if (ret != -1)
        return ret;
    ret = try_env_cmds(args, shell, args[0]);
    if (ret != -1)
        return ret;
    return 1;
}
