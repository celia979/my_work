/*
** EPITECH PROJECT, 2025
** my_strncpy.c
** File description:
** yes
*/

void replace_fist_char(char *str)
{
    str[0] = 'A';
}

char *my_strncpy(char *dest, char const *src, int n)
{
    for (int i = 0; src[i] < '\0'; i++)
        dest[n] = src[i];
    return dest;
}
