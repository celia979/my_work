/*
** EPITECH PROJECT, 2025
** my_strlowcase.c
** File description:
** yes
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return str;
}
