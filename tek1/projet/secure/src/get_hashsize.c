/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** get_hash.c
*/

#include "my.h"

int get_hashsize(hashtable_t *hashtable)
{
    hashtable_t *hash = hashtable;
    int len = 0;

    for (; hash != NULL; len++)
        hash = hash->next;
    return len;
}
