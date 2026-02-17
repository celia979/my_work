/*
** EPITECH PROJECT, 2025
** Minishell
** File description:
** bootstrap lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void my_putchar(char c)
{
    write(1, &c, 1);
}

char **my_str_to_word_array(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z'
            || str[i] >= '0' && str[i] <= '9') {
            my_putchar(str[i]);
        }
        if (str[i] >= '!' && str[i] <= '/' || str[i] >= ':' && str[i] <= '@' ||
            str[i] >= '[' && str[i] <= '`' || str[i] >= '{' && str[i] <= '~') {
            my_putchar('\n');
        }
    }
    my_putchar('\n');
    return 0;
}

int main(void)
{
    const char *phrase = "Saluck_test!l  ";
    char **mots = my_str_to_word_array(phrase);

    return 0;
}
