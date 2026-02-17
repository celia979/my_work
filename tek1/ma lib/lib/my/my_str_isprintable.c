/*
** EPITECH PROJECT, 2025
** my_str_isprintable.c
** File description:
** yes
*/

int my_str_isprintable(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 33 && str[i] <= 126) {
            return 1;
        } else
            return 0;
        if (str[i] == 0)
            return 1;
    }
    return 0;
}
