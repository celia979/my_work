/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** get current user
*/

#include "my.h"

int my_get_users(void)
{
    int count = -1;
    struct utmp *entry = NULL;

    setutent();
    entry = getutent();
    while (entry != NULL) {
        if (entry->ut_type == USER_PROCESS)
            count++;
        entry = getutent();
    }
    endutent();
    return count;
}
