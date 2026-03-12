/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** print_the_header
*/

#include "my.h"

int print_header(system_info_t *sys)
{
    time_info_t time_info = {0};
    int users = 0;

    my_get_time(&time_info);
    users = my_get_users();
    print_top_line(&time_info, users, sys->loadavg);
    print_tasks_line(sys->task);
    print_cpu_line(sys->cpu);
    print_mem_line(sys->mem);
    print_swap_line(sys->swap, sys->mem);
    return 0;
}
