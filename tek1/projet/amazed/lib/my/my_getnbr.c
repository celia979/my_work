/*
** EPITECH PROJECT, 2026
** my_get_nbr
** File description:
** Find number in a string
*/

int my_getnbr(char const *str)
{
    int i = 0;
    int res = 0;

    if (!str)
        return 0;
    while (str[i] && (str[i] < '0' || str[i] > '9'))
        i++;
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}
