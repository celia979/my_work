/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Built-in commands: cd, env, exit
*/

#include "../../include/mysh.h"

int builtin_env(char **args, shell_t *shell)
{
    env_t *cur = shell->env;

    (void)args;
    while (cur) {
        write(1, cur->key, my_strlen(cur->key));
        write(1, "=", 1);
        write(1, cur->value, my_strlen(cur->value));
        write(1, "\n", 1);
        cur = cur->next;
    }
    return 0;
}

int builtin_exit(char **args, shell_t *shell)
{
    int code = shell->last_status;

    if (args[1])
        code = my_atoi(args[1]);
    destroy_shell(shell);
    exit(code);
}

static void cd_error(char const *path)
{
    write(2, "cd: can't cd to ", 16);
    write(2, path, my_strlen(path));
    write(2, "\n", 1);
}

int builtin_cd(char **args, shell_t *shell)
{
    char const *path = NULL;
    char cwd[4096];
    char *home = NULL;

    if (!args[1]) {
        home = get_env_value(shell->env, "HOME");
        path = home ? home : "/";
    } else {
        path = args[1];
    }
    if (chdir(path) == -1) {
        cd_error(path);
        return 1;
    }
    if (getcwd(cwd, sizeof(cwd)))
        set_env_value(&shell->env, "PWD", cwd);
    return 0;
}
