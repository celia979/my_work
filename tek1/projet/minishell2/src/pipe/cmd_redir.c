/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** Redirection token detection and application
*/

#include "../../include/mysh.h"

int is_redir_tok(char const *tok)
{
    return (my_strcmp(tok, ">") == 0 || my_strcmp(tok, ">>") == 0
        || my_strcmp(tok, "<") == 0 || my_strcmp(tok, "<<") == 0);
}

static void apply_out_redir(redir_t *redir, char const *op, char const *file)
{
    free(redir->out_file);
    redir->out_file = my_strdup(file);
    redir->append = (my_strcmp(op, ">>") == 0) ? 1 : 0;
}

static void apply_in_redir(redir_t *redir, char const *op, char const *file)
{
    if (my_strcmp(op, "<") == 0) {
        free(redir->in_file);
        redir->in_file = my_strdup(file);
    } else {
        free(redir->heredoc);
        redir->heredoc = my_strdup(file);
    }
}

void apply_redir(redir_t *redir, char const *op, char const *file)
{
    if (my_strcmp(op, ">") == 0 || my_strcmp(op, ">>") == 0)
        apply_out_redir(redir, op, file);
    else
        apply_in_redir(redir, op, file);
}

static void fill_one_arg(cmd_t *cmd, char **toks, int *ti, int *ai)
{
    if (is_redir_tok(toks[*ti]) && toks[*ti + 1]) {
        apply_redir(&cmd->redir, toks[*ti], toks[*ti + 1]);
        *ti += 2;
    } else {
        cmd->args[*ai] = my_strdup(toks[*ti]);
        *ai += 1;
        *ti += 1;
    }
}

void fill_cmd_args(cmd_t *cmd, char **toks)
{
    int tok_i = 0;
    int arg_i = 0;

    while (toks[tok_i])
        fill_one_arg(cmd, toks, &tok_i, &arg_i);
    cmd->args[arg_i] = NULL;
}
