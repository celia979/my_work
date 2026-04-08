/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** Single command execution (fork, exec, builtins)
*/

#include "../../include/mysh.h"

static void child_exec(shell_t *shell, cmd_t *cmd)
{
    char **envp = env_to_array(shell->env);
    char *binary = NULL;

    if (setup_redirections(&cmd->redir) == -1)
        exit(84);
    if (is_builtin(cmd->args[0]))
        exit(exec_builtin(cmd->args, shell));
    binary = find_binary(cmd->args[0], envp);
    if (!binary) {
        write(2, cmd->args[0], my_strlen(cmd->args[0]));
        write(2, ": Command not found.\n", 21);
        exit(84);
    }
    execve(binary, cmd->args, envp);
    perror(cmd->args[0]);
    exit(84);
}

static int get_child_status(int wstatus)
{
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus))
        return 128 + WTERMSIG(wstatus);
    return 0;
}

static int do_fork_wait(shell_t *shell, cmd_t *cmd)
{
    int wstatus = 0;
    pid_t pid = fork();

    if (pid == -1)
        return 84;
    if (pid == 0)
        child_exec(shell, cmd);
    waitpid(pid, &wstatus, 0);
    return get_child_status(wstatus);
}

int run_cmd(shell_t *shell, cmd_t *cmd)
{
    if (!cmd->args || !cmd->args[0])
        return 0;
    if (is_builtin(cmd->args[0])) {
        if (setup_redirections(&cmd->redir) == -1)
            return 84;
        return exec_builtin(cmd->args, shell);
    }
    return do_fork_wait(shell, cmd);
}
