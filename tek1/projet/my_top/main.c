/*
** EPITECH PROJECT, 2026
** fctn
** File description:
** renseigner tout les fctn different
*/

#include "my.h"

void tableau(flag_t *flag)
{
    task_t **fld_lst = take_fld("/proc");

    fill_task(fld_lst);
    print_tab(fld_lst, flag->user);
    free_task(fld_lst);
    return;
}

void fill_system_info(system_info_t *sys)
{
    my_getloadavg(sys->loadavg);
    my_getmemory(sys->mem);
    my_getswap(sys->swap);
    my_getcpu(sys->cpu, sys->prev_cpu);
    my_gettask(sys->task);
}

void header(void)
{
    system_info_t sys = {0};

    fill_system_info(&sys);
    print_header(&sys);
}

void loop(flag_t *flag)
{
    while (flag->nb_refresh != 1) {
        clear();
        header();
        tableau(flag);
        refresh();
        if (getch() == 'q')
            break;
        flag->nb_refresh--;
    }
}

int main(int ac, char **av)
{
    flag_t *flag = get_flag(av);

    if ((flag->error != 0) || (ac % 2 == 0))
        return 84;
    initscr();
    timeout(flag->spr * 1000);
    loop(flag);
    endwin();
    free(flag);
    return 0;
}
