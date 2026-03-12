/*
** EPITECH PROJECT, 2026
** fctn
** File description:
** renseigner tout les fctn different
*/

#include "my.h"

int my_getmemory(double mem[])
{
    mem[0] = (get_value_in_proc("MemTotal", "meminfo") / 1024);
    mem[1] = (get_value_in_proc("MemFree", "meminfo") / 1024);
    mem[2] = (get_value_in_proc("MemAvailable", "meminfo") / 1024);
    mem[3] = (get_value_in_proc("Cached", "meminfo") / 1024);
    mem[4] = (get_value_in_proc("Buffers", "meminfo") / 1024);
    return 0;
}
