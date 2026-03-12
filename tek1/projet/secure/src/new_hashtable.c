/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** new_hashtable
*/

#include "my.h"

hashtable_t *init_hash(int(*hash)(char *, int), hashtable_t *next_hash)
{
    hashtable_t *n_hash = malloc(sizeof(hashtable_t));

    if (n_hash == NULL) {
        print("error malloc");
        return NULL;
    }
    n_hash->hash = hash;
    n_hash->next = next_hash;
    n_hash->same_id = NULL;
    n_hash->key = -1;
    n_hash->value = NULL;
    return n_hash;
}

hashtable_t *new_hashtable(int(*hash)(char *, int), int len)
{
    hashtable_t *new_hashtable;

    if (len <= 0)
        return NULL;
    new_hashtable = init_hash(hash, NULL);
    if (new_hashtable == NULL) {
        print("error malloc");
        return NULL;
    }
    for (int i = 1; i < len; i++) {
        new_hashtable = init_hash(hash, new_hashtable);
    }
    return new_hashtable;
}
