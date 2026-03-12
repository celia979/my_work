/*
** EPITECH PROJECT, 2026
** fctn
** File description:
** renseigner tout les fctn different
*/

#include "my.h"

int my_getswap(double swap[])
{
    swap[0] = (get_value_in_proc("SwapTotal", "meminfo") / 1024);
    swap[1] = (get_value_in_proc("SwapFree", "meminfo") / 1024);
    swap[3] = (get_value_in_proc("SwapCached", "meminfo") / 1024);
    swap[2] = 0;
    return 0;
}
