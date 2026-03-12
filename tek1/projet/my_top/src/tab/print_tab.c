/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** print_tab
*/

#include "my.h"

int static print_cmd(task_t **task_lst, int *space, char *user)
{
    int add_space = 8;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%3s", task_lst[i]->cmd_name);
            pos++;
        }
        if (add_space < my_strlen(task_lst[i]->cmd_name) + 1)
            add_space = my_strlen(task_lst[i]->cmd_name) + 1;
    }
    mvprintw(6, *space, "COMMAND");
    *space += add_space;
    return 0;
}

int static print_stat(task_t **task_lst, int *space, char *user)
{
    int add_space = 2;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%s", task_lst[i]->stat);
            pos++;
        }
    }
    mvprintw(6, *space, "S");
    *space += add_space;
    return 0;
}

int static print_shr(task_t **fld_list, int *space, char *user)
{
    int add_space = 4;

    mvprintw(6, *space + 1, "SHR");
    *space += add_space + 1;
    return 0;
}

int static print_res(task_t **fld_list, int *space, char *user)
{
    int add_space = 4;

    mvprintw(6, *space + 1, "RES");
    *space += add_space + 1;
    return 0;
}

int static print_virt(task_t **fld_list, int *space, char *user)
{
    int add_space = 5;

    mvprintw(6, *space + 1, "VIRT");
    *space += add_space + 1;
    return 0;
}

int static print_ni(task_t **task_lst, int *space, char *user)
{
    int add_space = 3;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%3s", task_lst[i]->niceness);
            pos++;
        }
        if (add_space < my_strlen(task_lst[i]->niceness) + 1 &&
            task_lst[i]->niceness[0] != '-')
            add_space = my_strlen(task_lst[i]->niceness) + 1;
    }
    mvprintw(6, *space + 1, "NI");
    *space += add_space + 1;
    return 0;
}

int static print_pr(task_t **task_lst, int *space, char *user)
{
    int add_space = 3;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%3s", task_lst[i]->priority);
            pos++;
        }
        if (add_space < my_strlen(task_lst[i]->priority) + 1 &&
            task_lst[i]->priority[0] != '-')
            add_space = my_strlen(task_lst[i]->priority) + 1;
    }
    mvprintw(6, *space + 1, "PR");
    *space += add_space + 1;
    return 0;
}

int static print_user(task_t **task_lst, int *space, char *user)
{
    int add_space = 5;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%3s", task_lst[i]->user);
            pos++;
        }
        if (add_space < my_strlen(task_lst[i]->user) + 1)
            add_space = my_strlen(task_lst[i]->user) + 1;
    }
    mvprintw(6, *space, "USER");
    *space += add_space;
    return 0;
}

int static print_pid(task_t **task_lst, int *space, char *user)
{
    int add_space = 4;
    int pos = 0;

    for (int i = 0; task_lst[i] != NULL; i++) {
        if ((my_strcmp(task_lst[i]->user, user) == 0) ||
            (my_strcmp("all", user) == 0)) {
            mvprintw(7 + pos, *space, "%3s", task_lst[i]->pid);
            pos++;
        }
        if (add_space < my_strlen(task_lst[i]->pid) + 1)
            add_space = my_strlen(task_lst[i]->pid) + 1;
    }
    mvprintw(6, *space, "PID");
    *space += add_space;
    return 0;
}

int print_tab(task_t **task_lst, char *user)
{
    int space = 0;

    print_pid(task_lst, &space, user);
    print_user(task_lst, &space, user);
    print_pr(task_lst, &space, user);
    print_ni(task_lst, &space, user);
    print_virt(task_lst, &space, user);
    print_res(task_lst, &space, user);
    print_shr(task_lst, &space, user);
    print_stat(task_lst, &space, user);
    print_cmd(task_lst, &space, user);
    return 0;
}

//PID USER PR NI VIRT RES SHR S %CPU %MEM TIME+ COMMAND
