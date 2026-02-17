/*
** EPITECH PROJECT, 2025
** my_str_isupper.c
** File description:
** yes
*/

int my_str_isupper(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            return 1;
        } else
            return 0;
        if (str[i] == 0)
            return 1;
    }
    return 0;
}
