/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Memory cleanup for pipeline and cmd structures
*/

#include "../../include/mysh.h"

void free_cmd(cmd_t *cmd)
{
    if (!cmd)
        return;
    free_args(cmd->args);
    free(cmd->redir.in_file);
    free(cmd->redir.out_file);
    free(cmd->redir.heredoc);
    free(cmd);
}

void free_pipeline_list(pipeline_t *list)
{
    pipeline_t *pl_next = NULL;
    cmd_t *cmd = NULL;
    cmd_t *cmd_next = NULL;

    while (list) {
        pl_next = list->next;
        cmd = list->cmds;
        while (cmd) {
            cmd_next = cmd->next;
            free_cmd(cmd);
            cmd = cmd_next;
        }
        free(list);
        list = pl_next;
    }
}
