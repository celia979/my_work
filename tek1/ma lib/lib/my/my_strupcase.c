/*
** EPITECH PROJECT, 2025
** my_strupcase.c
** File description:
** yes
*/

char *my_strupcase(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return str;
}
