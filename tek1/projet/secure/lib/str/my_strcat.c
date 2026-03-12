/*
** EPITECH PROJECT, 2026
** my_strcat
** File description:
** concatenate first str with the seconde
*/

#include "my_str.h"

char *my_strcat(char *s1, char const *s2)
{
    char *str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
    int position = 0;
    int letter = 0;

    if (str == NULL)
        return NULL;
    for (position = 0; position < my_strlen(s1); position++) {
        str[position] = s1[position];
    }
    for (letter = 0; letter < my_strlen(s2); letter++) {
        str[position + letter] = s2[letter];
    }
    str[position + letter] = '\0';
    return str;
}
