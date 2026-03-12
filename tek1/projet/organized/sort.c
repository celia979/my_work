/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Sort command
*/

#include "shell.h"
#include "struct.h"
#include <stdlib.h>

static int is_valid_criterion(char const *criterion)
{
    if (my_strcmp(criterion, "TYPE") == 0)
        return 1;
    if (my_strcmp(criterion, "NAME") == 0)
        return 1;
    if (my_strcmp(criterion, "ID") == 0)
        return 1;
    if (my_strcmp(criterion, "-r") == 0)
        return 1;
    return 0;
}

static int get_comparison_value(hardware_t *h1, hardware_t *h2,
    char *criterion)
{
    if (my_strcmp(criterion, "TYPE") == 0)
        return h1->type - h2->type;
    if (my_strcmp(criterion, "NAME") == 0)
        return my_strcmp(h1->name, h2->name);
    if (my_strcmp(criterion, "ID") == 0)
        return h1->id - h2->id;
    return 0;
}

static int compare_hardware(hardware_t *h1, hardware_t *h2,
    sort_params_t *params)
{
    int cmp = 0;
    int i = 0;

    while (i < params->nb_criteria && cmp == 0) {
        cmp = get_comparison_value(h1, h2, params->criteria[i]);
        if (params->reverse_flags[i])
            cmp = -cmp;
        i++;
    }
    return cmp;
}

static void swap_nodes(linked_list_t *a, linked_list_t *b)
{
    void *temp = a->data;

    a->data = b->data;
    b->data = temp;
}

static void apply_reverse_flag(int *reverse_flags, int nb_criteria)
{
    if (nb_criteria > 0)
        reverse_flags[nb_criteria - 1] = 1;
}

static int parse_criteria(char **args, char **criteria,
    int *reverse_flags, int *nb_criteria)
{
    int i = 0;
    int is_reverse = 0;

    while (args[i] != NULL) {
        if (!is_valid_criterion(args[i]))
            return 84;
        is_reverse = (my_strcmp(args[i], "-r") == 0);
        if (is_reverse)
            apply_reverse_flag(reverse_flags, *nb_criteria);
        if (!is_reverse) {
            criteria[*nb_criteria] = args[i];
            reverse_flags[*nb_criteria] = 0;
            (*nb_criteria)++;
        }
        i++;
    }
    return 0;
}

static int should_swap(linked_list_t *current, sort_params_t *params)
{
    hardware_t *hw1 = (hardware_t *)current->data;
    hardware_t *hw2 = (hardware_t *)current->next->data;

    return compare_hardware(hw1, hw2, params) > 0;
}

static int perform_bubble_pass(linked_list_t *list, sort_params_t *params)
{
    linked_list_t *current = list;
    int swapped = 0;

    while (current != NULL && current->next != NULL) {
        if (should_swap(current, params)) {
            swap_nodes(current, current->next);
            swapped = 1;
        }
        current = current->next;
    }
    return swapped;
}

static void sort_list(linked_list_t **list, sort_params_t *params)
{
    int swapped = 1;

    if (*list == NULL || params->nb_criteria == 0)
        return;
    while (swapped)
        swapped = perform_bubble_pass(*list, params);
}

int sort(void *data, char **args)
{
    linked_list_t **list = (linked_list_t **)data;
    char *criteria[10];
    int reverse_flags[10];
    sort_params_t params;

    params.criteria = criteria;
    params.reverse_flags = reverse_flags;
    params.nb_criteria = 0;
    if (args == NULL || args[0] == NULL)
        return 84;
    if (parse_criteria(args, params.criteria, params.reverse_flags,
            &params.nb_criteria) != 0)
        return 84;
    sort_list(list, &params);
    return 0;
}
