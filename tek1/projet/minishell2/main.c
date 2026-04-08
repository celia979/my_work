/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Entry point of mysh
*/

#include "./include/mysh.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    write(1, PROMPT, my_strlen(PROMPT));
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = NULL;

    (void)argv;
    if (argc != 1) {
        write(2, "Usage: ./mysh\n", 14);
        return 84;
    }
    signal(SIGINT, handle_sigint);
    shell = init_shell(env);
    if (!shell)
        return 84;
    run_shell(shell);
    destroy_shell(shell);
    return 0;
}
