/*
** EPITECH PROJECT, 2025
** my_strlen.c
** File description:
** yes
*/
#include <unistd.h>

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i = i + 1;
    }
    return 0;
}
