/*
** EPITECH PROJECT, 2025
** width.c
** File description:
** width
*/

#include "my.h"

int print_spaces(int n)
{
    int i = 0;

    while (i < n) {
        my_putchar(' ');
        i = i + 1;
    }
    return (n);
}

int handle_width(int width, int current_len)
{
    int count = 0;
    int i = 0;

    while (i < width - current_len) {
        my_putchar(' ');
        i = i + 1;
        count = count + 1;
    }
    return (count);
}
