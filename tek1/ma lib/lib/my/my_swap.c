/*
** EPITECH PROJECT, 2025
** my_swap.c
** File description:
** yes
*/

#include <unistd.h>

void my_swap(int *a, int *b)
{
    int d;

    d = *a;
    *a = *b;
    *b = d;
}

int that_uo(int *a, int *b)
{
    my_swap(a, b);
    return 0;
}
