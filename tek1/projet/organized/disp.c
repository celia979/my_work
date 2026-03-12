/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Display command
*/

#include "shell.h"
#include "struct.h"
#include <stddef.h>

int disp(void *data, char **args)
{
    linked_list_t **list = (linked_list_t **)data;
    linked_list_t *current = *list;
    hardware_t *hardware;

    (void)args;
    while (current != NULL) {
        hardware = (hardware_t *)current->data;
        my_putstr(get_type_string(hardware->type));
        my_putstr(" n°");
        my_put_nbr(hardware->id);
        my_putstr(" - \"");
        my_putstr(hardware->name);
        my_putstr("\"\n");
        current = current->next;
    }
    return 0;
}
