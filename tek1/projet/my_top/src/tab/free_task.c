/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** free_task
*/

#include "my.h"

int free_task(task_t **task_lst)
{
    for (int i = 0; task_lst[i] != NULL; i++) {
        free(task_lst[i]->pid);
        free(task_lst[i]->uid);
        free(task_lst[i]->user);
        free(task_lst[i]->cmd_name);
        free(task_lst[i]->stat);
        free(task_lst[i]->priority);
        free(task_lst[i]->niceness);
        free(task_lst[i]->file_path_stat);
        free(task_lst[i]->fpath_status);
        free(task_lst[i]);
    }
    free(task_lst);
    return 0;
}
