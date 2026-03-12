/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Display a character
*/

#include "../../include/my.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}
