/*
** EPITECH PROJECT, 2026
** my_putstr
** File description:
** print un str
*/

int my_strlen(char const *str)
{
    int nbchar = 0;

    while (str[nbchar] != '\0') {
        nbchar += 1;
    }
    return nbchar;
}
