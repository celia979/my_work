/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** ht_search
*/

#include "my.h"

char *ht_search(hashtable_t *ht, char *key)
{
    int pos;
    int nb_key;

    if (ht == NULL || key == NULL)
        return NULL;
    nb_key = ht->hash(key, 7);
    pos = nb_key % get_hashsize(ht);
    for (int i = 0; i < pos; i++)
        ht = ht->next;
    for (; ht != NULL; ht = ht->same_id)
        if (ht->key == nb_key)
            return ht->value;
    return NULL;
}
