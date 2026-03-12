/*
** EPITECH PROJECT, 2026
** my_strcmp
** File description:
** trouver la diff entre 2 str
*/

#include "my_str.h"

int my_strcmp(char const *s1, char const *s2)
{
    if (my_strlen(s1) != my_strlen(s2))
        return 84;
    for (int letter = 0; s1[letter] != '\0' && s2[letter] != '\0'; letter++) {
        if (s1[letter] != s2[letter])
            return s1[letter] - s2[letter];
    }
    return 0;
}
