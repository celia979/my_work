/*
** EPITECH PROJECT, 2025
** fctn
** File description:
** ht_delete
*/

#include "my.h"
#include "hashtable.h"

int del_seconde(hashtable_t *ht, int nb_key)
{
    hashtable_t *prev_ht = ht;

    ht = ht->same_id;
    while (ht != NULL && ht->key != nb_key) {
        prev_ht = ht;
        ht = ht->same_id;
    }
    if (ht != NULL) {
        prev_ht->same_id = ht->same_id;
        free_elem(ht);
        return 1;
    }
    return 0;
}

int del_first(hashtable_t *ht, int nb_key, hashtable_t *prev_ht)
{
    if (ht->key == nb_key) {
        if (ht->same_id != NULL) {
            prev_ht->next = ht->same_id;
            ht->same_id->next = ht->next;
            free_elem(ht);
        } else {
            free(ht->value);
            ht->value = NULL;
            ht->key = -1;
        }
        return 1;
    } else {
        return del_seconde(ht, nb_key) == 1;
    }
}

int del_zero_zero(int pos, hashtable_t *ht, int nb_key)
{
    hashtable_t *stocked;

    if (pos == 0 && ht->key == nb_key) {
        free(ht->value);
        ht->value = NULL;
        ht->key = -1;
        if (ht->same_id != NULL) {
            stocked = ht->same_id;
            ht->same_id = stocked->same_id;
            ht->value = stocked->value;
            ht->key = stocked->key;
            free(stocked);
        }
        return 1;
    }
    return 0;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int nb_key;
    int pos;
    hashtable_t *prev_ht = ht;

    if (ht == NULL || key == NULL)
        return 84;
    nb_key = ht->hash(key, 7);
    pos = nb_key % get_hashsize(ht);
    if (del_zero_zero(pos, ht, nb_key) == 1)
        return 0;
    if (pos > 0) {
        ht = ht->next;
        for (int i = 1; i < pos; i++) {
            prev_ht = ht;
            ht = ht->next;
        }
    }
    if (del_first(ht, nb_key, prev_ht) == 1)
        return 0;
    return 84;
}
