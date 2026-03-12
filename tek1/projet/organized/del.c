/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Delete command
*/

#include "shell.h"
#include "struct.h"
#include <stdlib.h>

static int my_atoi(char const *str)
{
    int result = 0;
    int i = 0;
    int sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

static int is_valid_number(char const *str)
{
    int i = 0;

    if (str[i] == '-')
        i++;
    if (str[i] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

static void print_deleted_hardware(hardware_t *hardware)
{
    my_putstr(get_type_string(hardware->type));
    my_putstr(" n°");
    my_put_nbr(hardware->id);
    my_putstr(" - \"");
    my_putstr(hardware->name);
    my_putstr("\" deleted.\n");
}

static void free_hardware_node(linked_list_t *node)
{
    hardware_t *hw = (hardware_t *)node->data;

    free(hw->name);
    free(hw);
    free(node);
}

static void delete_first_node(linked_list_t **list, hardware_t *hw)
{
    linked_list_t *current = *list;

    print_deleted_hardware(hw);
    *list = current->next;
    free_hardware_node(current);
}

static void delete_middle_node(linked_list_t *prev, linked_list_t *current)
{
    hardware_t *hw = (hardware_t *)current->data;

    print_deleted_hardware(hw);
    prev->next = current->next;
    free_hardware_node(current);
}

static int check_and_delete_node(linked_list_t **list, linked_list_t *prev,
    linked_list_t *current, int id)
{
    hardware_t *hw = (hardware_t *)current->data;

    if (hw->id != id)
        return 0;
    if (prev == NULL)
        delete_first_node(list, hw);
    else
        delete_middle_node(prev, current);
    return 1;
}

static int delete_by_id(linked_list_t **list, int id)
{
    linked_list_t *current = *list;
    linked_list_t *prev = NULL;

    while (current != NULL) {
        if (check_and_delete_node(list, prev, current, id))
            return 0;
        prev = current;
        current = current->next;
    }
    return 84;
}

int del(void *data, char **args)
{
    linked_list_t **list = (linked_list_t **)data;
    int i = 0;
    int id;

    if (args == NULL || args[0] == NULL)
        return 84;
    while (args[i] != NULL) {
        if (!is_valid_number(args[i]))
            return 84;
        id = my_atoi(args[i]);
        if (delete_by_id(list, id) != 0)
            return 84;
        i++;
    }
    return 0;
}
