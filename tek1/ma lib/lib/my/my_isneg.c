/*
** EPITECH PROJECT, 2025
** my_isneg.c
** File description:
** yes
*/
#include <unistd.h>
#include "../../include/my.h"

int my_isneg(int n)
{
    if (n >= 0) {
        my_putchar('P');
    } else {
        my_putchar('N');
    }
    my_putchar('\n');
    return 0;
}
