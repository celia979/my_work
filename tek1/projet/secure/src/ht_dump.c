/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** ht_dump
*/

#include "my.h"

void print_value(hashtable_t *cur_ht)
{
    for (hashtable_t *a_ht = cur_ht; a_ht != NULL; a_ht = a_ht->same_id)
        if (a_ht->value != NULL)
            print("> %i - %s\n", a_ht->key, a_ht->value);
}

void ht_dump(hashtable_t *ht)
{
    hashtable_t *cur_ht = ht;

    for (int nb = 0; cur_ht != NULL; cur_ht = cur_ht->next) {
        print("[%i]:\n", nb);
        print_value(cur_ht);
        nb += 1;
    }
    return;
}
