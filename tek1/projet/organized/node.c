/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Linked list manipulation
*/

#include "struct.h"
#include <unistd.h>
#include <stdlib.h>

int push_to_list(linked_list_t **begin, void *data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (new_node == NULL)
        return 84;
    new_node->data = data;
    new_node->next = *begin;
    *begin = new_node;
    return 0;
}
