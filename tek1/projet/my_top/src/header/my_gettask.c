/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** get task information
*/

#include "my.h"

int my_gettask(double task[])
{
    DIR *dir = opendir("/proc");
    struct dirent *entry = NULL;
    int total = 0;

    if (dir == NULL)
        return 84;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
            total++;
        entry = readdir(dir);
    }
    closedir(dir);
    task[0] = total;
    task[1] = count_state('R');
    task[2] = count_state('S');
    task[3] = count_state('T');
    task[4] = count_state('Z');
    return 0;
}
