/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** delete_hashtable
*/

#include "my.h"

void delete_hashtable(hashtable_t *ht)
{
    if (ht == NULL)
        return;
    if (ht->next != NULL)
        delete_hashtable(ht->next);
    if (ht->same_id != NULL)
        delete_hashtable(ht->same_id);
    free_elem(ht);
    return;
}
