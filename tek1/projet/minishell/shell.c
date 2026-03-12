/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Shell loop and initialization
*/

#include "mysh.h"

shell_t *init_shell(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return NULL;
    shell->env = parse_env(env);
    shell->last_status = 0;
    return shell;
}

void destroy_shell(shell_t *shell)
{
    if (!shell)
        return;
    free_env(shell->env);
    free(shell);
}

static int process_line(char *line, shell_t *shell)
{
    char **args = NULL;
    int status = 0;
    int len = my_strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    if (line[0] == '\0')
        return 0;
    args = split_args(line);
    if (!args || !args[0]) {
        free_args(args);
        return 0;
    }
    status = execute_command(args, shell);
    free_args(args);
    return status;
}

void run_shell(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            write(1, PROMPT, my_strlen(PROMPT));
        nread = getline(&line, &len, stdin);
        if (nread == -1)
            break;
        shell->last_status = process_line(line, shell);
    }
    free(line);
}
