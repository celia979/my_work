/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** get cpu usage information
*/

#include "my.h"

int my_getcpu(double cpu[], double prev[])
{
    FILE *file = fopen("/proc/stat", "r");
    double stats[7] = {0};

    if (file == NULL)
        return 84;
    fscanf(file, "cpu %lf %lf %lf %lf %lf %lf %lf",
        &stats[0], &stats[1], &stats[2], &stats[3],
        &stats[4], &stats[5], &stats[6]);
    fclose(file);
    calculate_cpu(cpu, stats, prev);
    return 0;
}

void calculate_cpu(double *cpu, double *stats, double *prev)
{
    double delta[7] = {0};
    double total = 0;
    int i = 0;

    for (i = 0; i < 7; i++) {
        delta[i] = stats[i] - prev[i];
        total += delta[i];
        prev[i] = stats[i];
    }
    if (total == 0)
        return;
    for (i = 0; i < 7; i++)
        cpu[i] = (delta[i] / total) * 100;
}
