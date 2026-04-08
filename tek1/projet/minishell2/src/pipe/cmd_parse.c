/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** Command segment tokenization and building
*/

#include "../../include/mysh.h"

static int count_tokens(char const *seg)
{
    char *copy = my_strdup(seg);
    char *saveptr = NULL;
    int count = 0;

    if (!copy)
        return 0;
    while (strtok_r(count == 0 ? copy : NULL, " \t", &saveptr))
        count++;
    free(copy);
    return count;
}

static void fill_loop(char **toks, char *copy, int count)
{
    char *saveptr = NULL;
    char *tok = strtok_r(copy, " \t", &saveptr);
    int i = 0;

    while (tok && i < count) {
        toks[i] = my_strdup(tok);
        i++;
        tok = strtok_r(NULL, " \t", &saveptr);
    }
    toks[i] = NULL;
}

static char **fill_toks(char const *seg, int count)
{
    char *copy = my_strdup(seg);
    char **toks = malloc(sizeof(char *) * (count + 1));

    if (!copy || !toks) {
        free(copy);
        free(toks);
        return NULL;
    }
    fill_loop(toks, copy, count);
    free(copy);
    return toks;
}

static char **tokenize_segment(char const *seg)
{
    int count = count_tokens(seg);

    if (count == 0)
        return NULL;
    return fill_toks(seg, count);
}

static int count_real_args(char **toks)
{
    int count = 0;
    int i = 0;

    while (toks[i]) {
        if (is_redir_tok(toks[i]))
            i += 2;
        else {
            count++;
            i++;
        }
    }
    return count;
}

static cmd_t *init_cmd(void)
{
    cmd_t *cmd = malloc(sizeof(cmd_t));

    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->redir.in_file = NULL;
    cmd->redir.out_file = NULL;
    cmd->redir.heredoc = NULL;
    cmd->redir.append = 0;
    cmd->next = NULL;
    return cmd;
}

static cmd_t *alloc_cmd_args(int argc)
{
    cmd_t *cmd = init_cmd();

    if (!cmd)
        return NULL;
    cmd->args = malloc(sizeof(char *) * (argc + 1));
    if (!cmd->args) {
        free(cmd);
        return NULL;
    }
    return cmd;
}

static cmd_t *build_cmd(char **toks)
{
    cmd_t *cmd = alloc_cmd_args(count_real_args(toks));

    if (!cmd)
        return NULL;
    fill_cmd_args(cmd, toks);
    return cmd;
}

cmd_t *parse_segment(char *segment)
{
    char **toks = tokenize_segment(segment);
    cmd_t *cmd = NULL;

    if (!toks)
        return NULL;
    cmd = build_cmd(toks);
    free_args(toks);
    if (!cmd)
        return NULL;
    if (!cmd->args[0]) {
        free_cmd(cmd);
        return NULL;
    }
    return cmd;
}
