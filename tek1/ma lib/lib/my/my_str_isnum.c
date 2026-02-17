/*
** EPITECH PROJECT, 2025
** my_str_isnum.c
** File description:
** yes
*/

int my_str_isnum(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            return 1;
        } else
            return 0;
        if (str[i] == 0)
            return 1;
    }
    return 0;
}
