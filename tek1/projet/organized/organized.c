/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Main program
*/

#include "shell.h"
#include "struct.h"
#include <stdlib.h>

int main(void)
{
    linked_list_t *list = NULL;
    int ret = 0;

    ret = workshop_shell(&list);
    if (ret == 84)
        return 84;
    return 0;
}
