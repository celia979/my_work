/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get load avg
*/

#include "my.h"

int my_getloadavg(double loadavg[])
{
    FILE *file = fopen("/proc/loadavg", "r");

    fscanf(file, "%lf %lf %lf", &(loadavg[0]), &(loadavg[1]), &(loadavg[2]));
    fclose(file);
    return 0;
}
