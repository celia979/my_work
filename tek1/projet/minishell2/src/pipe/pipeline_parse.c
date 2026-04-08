/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** Line parsing into pipeline list (semicolons and pipes)
*/

#include "../../include/mysh.h"

static void append_cmd(pipeline_t *pl, cmd_t *cmd, cmd_t **last)
{
    if (!cmd)
        return;
    if (!pl->cmds)
        pl->cmds = cmd;
    else
        (*last)->next = cmd;
    *last = cmd;
}

static pipeline_t *init_pipeline(void)
{
    pipeline_t *pl = malloc(sizeof(pipeline_t));

    if (!pl)
        return NULL;
    pl->cmds = NULL;
    pl->next = NULL;
    return pl;
}

static void iter_pipe_toks(pipeline_t *pl, char *copy)
{
    char *saveptr = NULL;
    char *tok = strtok_r(copy, "|", &saveptr);
    cmd_t *last = NULL;

    while (tok) {
        append_cmd(pl, parse_segment(tok), &last);
        tok = strtok_r(NULL, "|", &saveptr);
    }
}

static pipeline_t *build_pipeline(char *seg)
{
    pipeline_t *pl = init_pipeline();
    char *copy = my_strdup(seg);

    if (!pl || !copy) {
        free(pl);
        free(copy);
        return NULL;
    }
    iter_pipe_toks(pl, copy);
    free(copy);
    if (!pl->cmds) {
        free(pl);
        return NULL;
    }
    return pl;
}

static void append_pipeline(pipeline_t **head, pipeline_t **last,
    pipeline_t *pl)
{
    if (!*head)
        *head = pl;
    else
        (*last)->next = pl;
    *last = pl;
}

static void iter_semi_toks(pipeline_t **head, pipeline_t **last, char *copy)
{
    char *saveptr = NULL;
    char *tok = strtok_r(copy, ";", &saveptr);
    pipeline_t *pl = NULL;

    while (tok) {
        pl = build_pipeline(tok);
        if (pl)
            append_pipeline(head, last, pl);
        tok = strtok_r(NULL, ";", &saveptr);
    }
}

pipeline_t *parse_line(char *line)
{
    pipeline_t *head = NULL;
    pipeline_t *last = NULL;
    char *copy = my_strdup(line);

    if (!copy)
        return NULL;
    iter_semi_toks(&head, &last, copy);
    free(copy);
    return head;
}
