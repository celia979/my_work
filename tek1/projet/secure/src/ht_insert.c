/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** ht_insert
*/

#include "my.h"


hashtable_t *create_hash(char *value, int key,
    int(*hash)(char *, int), hashtable_t *same_id)
{
    hashtable_t *n_hash = malloc(sizeof(hashtable_t));

    n_hash->hash = hash;
    n_hash->value = value;
    n_hash->key = key;
    n_hash->same_id = same_id;
    n_hash->next = NULL;
    return n_hash;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int pos;

    if (ht == NULL || key == NULL || value == NULL)
        return 84;
    pos = ht->hash(key, 7) % get_hashsize(ht);
    for (int i = 0; i < pos; i++)
        ht = ht->next;
    if (ht->value == NULL) {
        ht->value = my_strdup(value);
        ht->key = ht->hash(key, 7);
        ht->same_id = NULL;
    } else {
        ht->same_id = create_hash(ht->value, ht->key, ht->hash, ht->same_id);
        ht->key = ht->hash(key, 7);
        ht->value = my_strdup(value);
    }
    return 0;
}
