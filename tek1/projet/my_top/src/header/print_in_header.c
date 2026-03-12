/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** print_the_header
*/

#include "my.h"

int print_top_line(time_info_t *info, int users, double avg[])
{
    printw("top - %02d:%02d:%02d up %s, %d user%s, ",
        info->hour, info->min, info->sec,
        info->uptime_str, users, users > 1 ? "s" : "");
    printw("load average: %.2f, %.2f, %.2f\n", avg[0], avg[1], avg[2]);
    return 0;
}

int print_tasks_line(double task[])
{
    printw("Tasks: %.0f total, %.0f running, %.0f sleeping, ",
        task[0], task[1], task[2]);
    printw("%.0f stopped, %.0f zombie\n", task[3], task[4]);
    return 0;
}

int print_cpu_line(double cpu[])
{
    printw("%%Cpu(s): %.1f us, %.1f sy, %.1f ni, %.1f id, ",
        cpu[0], cpu[1], cpu[2], cpu[3]);
    printw("%.1f wa, %.1f hi, %.1f si, %.1f st\n",
        cpu[4], cpu[5], cpu[6], 0.0);
    return 0;
}

int print_mem_line(double mem[])
{
    printw("MiB Mem : %.1f total, %.1f free, %.1f used, ",
        mem[0], mem[1], mem[0] - mem[2]);
    printw("%.1f buff/cache\n", mem[3] + mem[4]);
    return 0;
}

int print_swap_line(double swap[], double mem[])
{
    printw("MiB Swap: %.1f total, %.1f free, %.1f used, ",
        swap[0], swap[1], swap[2]);
    printw("%.1f avail Mem\n", mem[2]);
    return 0;
}
