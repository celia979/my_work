/*
** EPITECH PROJECT, 2025
** fctn
** File description:
** ht_delete
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "hashtable.h"
#include "my_str.h"

#ifndef MY_H
    #define MY_H

void free_elem(hashtable_t *ht);
int get_hashsize(hashtable_t *hashtable);
int print(const char *format, ...);

#endif /* !MY_H_*/
