/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** free_eelm
*/

#include "my.h"

void free_elem(hashtable_t *ht)
{
    if (ht->value != NULL)
        free(ht->value);
    free(ht);
}
