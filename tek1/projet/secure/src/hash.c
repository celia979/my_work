/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** hash
*/

#include "my.h"

long int my_fact(int nb)
{
    long int fact = 1;

    for (int i = 1; i < nb; i++) {
        fact *= i;
    }
    return fact;
}

int hash(char *key, int len)
{
    int key_nb = 0;

    for (int i = 0; key[i] != '\0'; i++)
        key_nb += key[i] * i;
    key_nb = key_nb << 4;
    for (int i = 0; i < len && key[i] != '\0'; i++)
        key_nb += key[i];
    key_nb ^= my_fact(my_strlen(key) % 13);
    key_nb += my_strlen(key);
    return key_nb;
}
