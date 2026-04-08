/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Pipeline and command execution with pipes and redirections
*/

#include "../../include/mysh.h"

static int count_cmds(cmd_t *cmd)
{
    int count = 0;

    while (cmd) {
        count++;
        cmd = cmd->next;
    }
    return count;
}

static void redirect_fds(int in_fd, int out_fd)
{
    if (in_fd != STDIN_FILENO) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO) {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

static void fork_piped_cmd(shell_t *shell, cmd_t *cmd,
    int in_fd, int out_fd)
{
    if (fork() == 0) {
        redirect_fds(in_fd, out_fd);
        run_cmd(shell, cmd);
        exit(84);
    }
}

static int wait_all_children(void)
{
    int wstatus = 0;
    int status = 0;

    while (wait(&wstatus) > 0)
        if (WIFEXITED(wstatus))
            status = WEXITSTATUS(wstatus);
    return status;
}

static void spawn_cmd(shell_t *shell, cmd_t *cmd,
    int in_fd, int pipefd[2])
{
    if (cmd->next)
        fork_piped_cmd(shell, cmd, in_fd, pipefd[1]);
    else
        fork_piped_cmd(shell, cmd, in_fd, STDOUT_FILENO);
}

static void rotate_fds(int *in_fd, int pipefd[2], cmd_t *cmd)
{
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (cmd->next) {
        close(pipefd[1]);
        *in_fd = pipefd[0];
    }
}

static int open_pipe_if_needed(cmd_t *cmd, int pipefd[2])
{
    if (!cmd->next)
        return 0;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

int run_pipeline(shell_t *shell, pipeline_t *pipeline)
{
    cmd_t *cmd = pipeline->cmds;
    int in_fd = STDIN_FILENO;
    int pipefd[2] = {0, 0};

    if (count_cmds(cmd) == 1)
        return run_cmd(shell, cmd);
    while (cmd) {
        if (open_pipe_if_needed(cmd, pipefd) == -1)
            return 84;
        spawn_cmd(shell, cmd, in_fd, pipefd);
        rotate_fds(&in_fd, pipefd, cmd);
        cmd = cmd->next;
    }
    return wait_all_children();
}

int run_pipeline_list(shell_t *shell, pipeline_t *list)
{
    pipeline_t *cur = list;
    int status = 0;

    while (cur) {
        status = run_pipeline(shell, cur);
        shell->last_status = status;
        cur = cur->next;
    }
    return status;
}
