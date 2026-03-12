/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Command execution using fork and execve
*/

#include "mysh.h"

static void free_arr(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static void handle_child(char *binary, char **args, shell_t *shell)
{
    char **envp = env_to_array(shell->env);

    execve(binary, args, envp);
    free_arr(envp);
    perror(args[0]);
    exit(84);
}

static int get_exit_status(int wstatus)
{
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus))
        return 128 + WTERMSIG(wstatus);
    return 0;
}

static char *resolve_binary(char **args, shell_t *shell)
{
    char **envp = env_to_array(shell->env);
    char *binary = find_binary(args[0], envp);

    free_arr(envp);
    return binary;
}

static int fork_and_exec(char *binary, char **args, shell_t *shell)
{
    pid_t pid = fork();
    int wstatus = 0;

    if (pid == -1) {
        perror("fork");
        free(binary);
        return 84;
    }
    if (pid == 0)
        handle_child(binary, args, shell);
    waitpid(pid, &wstatus, 0);
    free(binary);
    return get_exit_status(wstatus);
}

int execute_command(char **args, shell_t *shell)
{
    char *binary = NULL;

    if (is_builtin(args[0]))
        return exec_builtin(args, shell);
    binary = resolve_binary(args, shell);
    if (!binary) {
        write(STDERR_FILENO, args[0], my_strlen(args[0]));
        write(STDERR_FILENO, ": Command not found.\n", 21);
        return 1;
    }
    return fork_and_exec(binary, args, shell);
}
