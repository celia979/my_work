/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** free_task
*/

#include "my.h"

//PID USER PR NI VIRT RES SHR S %CPU %MEM TIME+ COMMAND

char *get_task_stat_str(int pos, task_t *task)
{
    char *file_path = my_strcat("/proc/", task->file_path_stat);
    FILE *file = fopen(file_path, "r");
    char *line = "";
    size_t size = 0;
    char *value;

    getline(&line, &size, file);
    if (pos == 1) {
        value = my_strdup(strtok(line, " "));
    } else {
        strtok(line, " ");
        for (int i = 0; i < (pos - 2); i++)
            strtok(NULL, " ");
        value = my_strdup(strtok(NULL, " "));
    }
    free(line);
    fclose(file);
    free(file_path);
    return value;
}

int get_task_stat_int(int pos, task_t *task)
{
    char *value_str = get_task_stat_str(pos, task);
    int value_int = my_strtoi(value_str);

    free(value_str);
    return value_int;
}

void get_name(task_t *task)
{
    char *command;

    task->cmd_name = get_task_stat_str(2, task);
    command = my_strdup(task->cmd_name + 1);
    command[my_strlen(command) - 1] = '\0';
    free(task->cmd_name);
    task->cmd_name = command;
}

int fill_task(task_t **task_lst)
{
    for (int i = 0; task_lst[i] != NULL; i++) {
        task_lst[i]->pid = get_task_stat_str(1, task_lst[i]);
        task_lst[i]->uid = get_str_in_proc("Uid", task_lst[i]->fpath_status);
        task_lst[i]->user = get_user(task_lst[i]->uid);
        get_name(task_lst[i]);
        task_lst[i]->stat = get_task_stat_str(3, task_lst[i]);
        task_lst[i]->priority = get_task_stat_str(18, task_lst[i]);
        if (my_strcmp(task_lst[i]->priority, "-100") == 0) {
            free(task_lst[i]->priority);
            task_lst[i]->priority = my_strdup("rt");
        }
        task_lst[i]->niceness = get_task_stat_str(19, task_lst[i]);
        task_lst[i]->virt = get_task_stat_int(23, task_lst[i]) / 1024;
        task_lst[i]->res = 0.0;
        task_lst[i]->shr = 0.0;
        task_lst[i]->cpu_use = 0.0;
        task_lst[i]->mem_use = 0.0;
        task_lst[i]->time = 0.0;
    }
    return 0;
}
