/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** flag
*/

#include "my.h"

int parssing(char **av, flag_t *flag, int *pos)
{
    if (my_strcmp(av[*pos], "-d") == 0) {
        flag->spr = my_strtof(av[*pos + 1]);
        return 0;
    }
    if (my_strcmp(av[*pos], "-n") == 0) {
        flag->nb_refresh = my_strtoi(av[*pos + 1]);
        return 0;
    }
    if (my_strcmp(av[*pos], "-u") == 0) {
        free(flag->user);
        flag->user = my_strdup(av[*pos + 1]);
        return 0;
    }
    return 84;
}

flag_t *get_flag(char **av)
{
    flag_t *flag = malloc(sizeof(flag_t) * 1);

    if (flag == NULL)
        return NULL;
    flag->spr = 3;
    flag->nb_refresh = 0;
    flag->user = my_strdup("all");
    flag->error = 0;
    for (int i = 1; (av[i] != NULL) && (flag->error == 0); i += 2) {
        if (av[i + 1] == NULL) {
            flag->error = 84;
        } else {
            flag->error = parssing(av, flag, &i);
        }
    }
    return flag;
}
