/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Redirections setup - >, >>, <, <<
*/

#include "../../include/mysh.h"

static int setup_output(redir_t const *redir)
{
    int flags = O_WRONLY | O_CREAT;
    int fd = 0;

    if (redir->append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(redir->out_file, flags, 0644);
    if (fd == -1) {
        perror(redir->out_file);
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

static int setup_input(redir_t const *redir)
{
    int fd = open(redir->in_file, O_RDONLY);

    if (fd == -1) {
        perror(redir->in_file);
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}

static int setup_heredoc(redir_t const *redir)
{
    int pipefd[2];
    char *line = NULL;
    size_t n = 0;
    int delim_len = my_strlen(redir->heredoc);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    while (getline(&line, &n, stdin) != -1) {
        if (my_strncmp(line, redir->heredoc, delim_len) == 0
            && (line[delim_len] == '\n' || line[delim_len] == '\0'))
            break;
        write(pipefd[1], line, my_strlen(line));
    }
    free(line);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    return 0;
}

int setup_redirections(redir_t const *redir)
{
    if (redir->in_file && setup_input(redir) == -1)
        return -1;
    if (redir->heredoc && setup_heredoc(redir) == -1)
        return -1;
    if (redir->out_file && setup_output(redir) == -1)
        return -1;
    return 0;
}
