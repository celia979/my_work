/*
** EPITECH PROJECT, 2025
** G-CPE-110 : Secured
** File description:
** hashtable.h
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef HASHTABLE_H
    #define HASHTABLE_H

typedef struct hashtable_s {
    char *value;
    int key;
    int(*hash)(char *, int);
    struct hashtable_s *same_id;
    struct hashtable_s *next;

} hashtable_t;

// Hash function
int hash(char *key, int len);

// Create & destro table
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);

// Handle table
int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);

#endif /* HASHTABLE_H */
