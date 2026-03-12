/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Add command
*/

#include "shell.h"
#include "struct.h"
#include <stdlib.h>

hardware_type_t get_type_from_string(char const *str)
{
    char const *types[] = {"ACTUATOR", "DEVICE", "PROCESSOR", "SENSOR",
        "WIRE", NULL};
    int i = 0;

    while (types[i] != NULL) {
        if (my_strcmp(str, types[i]) == 0)
            return (hardware_type_t)i;
        i++;
    }
    return (hardware_type_t)-1;
}

char *get_type_string(hardware_type_t type)
{
    char *types[] = {"ACTUATOR", "DEVICE", "PROCESSOR", "SENSOR", "WIRE"};

    if (type >= 0 && type <= WIRE)
        return types[type];
    return "UNKNOWN";
}

static void print_hardware_added(hardware_t *hardware)
{
    my_putstr(get_type_string(hardware->type));
    my_putstr(" n°");
    my_put_nbr(hardware->id);
    my_putstr(" - \"");
    my_putstr(hardware->name);
    my_putstr("\" added.\n");
}

static hardware_t *create_hardware(char *type_str, char *name, int id)
{
    hardware_t *hardware = malloc(sizeof(hardware_t));
    hardware_type_t type = get_type_from_string(type_str);

    if (hardware == NULL || type == (hardware_type_t)-1) {
        if (hardware != NULL)
            free(hardware);
        return NULL;
    }
    hardware->type = type;
    hardware->name = my_strdup(name);
    if (hardware->name == NULL) {
        free(hardware);
        return NULL;
    }
    hardware->id = id;
    return hardware;
}

static int get_next_id(linked_list_t *list)
{
    int next_id = 0;
    linked_list_t *current = list;
    hardware_t *hw;

    while (current != NULL) {
        hw = (hardware_t *)current->data;
        if (hw->id >= next_id)
            next_id = hw->id + 1;
        current = current->next;
    }
    return next_id;
}

static int add_single_hardware(linked_list_t **list,
    char *type_str, char *name, int *next_id)
{
    hardware_t *hardware = create_hardware(type_str, name, *next_id);

    if (hardware == NULL)
        return 84;
    (*next_id)++;
    if (push_to_list(list, hardware) != 0) {
        free(hardware->name);
        free(hardware);
        return 84;
    }
    print_hardware_added(hardware);
    return 0;
}

static int count_args(char **args)
{
    int count = 0;

    while (args[count] != NULL)
        count++;
    return count;
}

int add(void *data, char **args)
{
    linked_list_t **list = (linked_list_t **)data;
    int i = 0;
    int next_id = get_next_id(*list);
    int arg_count;

    if (args == NULL || args[0] == NULL)
        return 84;
    arg_count = count_args(args);
    if (arg_count % 2 != 0)
        return 84;
    while (args[i] != NULL && args[i + 1] != NULL) {
        if (add_single_hardware(list, args[i], args[i + 1], &next_id) != 0)
            return 84;
        i += 2;
    }
    return 0;
}
