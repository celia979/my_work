/*
** EPITECH PROJECT, 2025
** my_strlen.c
** File description:
** yes
*/
#include <unistd.h>

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len]) {
        len++;
    }
    return len;
}
