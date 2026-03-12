/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** count tasks by state
*/

#include "my.h"

static int check_state(char *name, char state)
{
    char path[256];
    char *stat_state = NULL;
    int match = 0;

    snprintf(path, sizeof(path), "%s/status", name);
    stat_state = get_str_in_proc("State", path);
    if (stat_state != NULL && stat_state[0] == state) {
        match = 1;
        free(stat_state);
    }
    return match;
}

int count_state(char state)
{
    DIR *dir = opendir("/proc");
    struct dirent *entry = NULL;
    int count = 0;

    if (dir == NULL)
        return 0;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
            count += check_state(entry->d_name, state);
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}
