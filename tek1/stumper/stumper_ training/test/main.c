/*
** EPITECH PROJECT, 2026
** B-CPE-210
** File description:
** Main function for French Name Formatter
*/

#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

static int should_uppercase_in_firstname(char const *name, int i)
{
    if (i == 0) {
        return 1;
    }
    if (name[i - 1] == '-') {
        return 1;
    }
    return 0;
}

static void process_first_name_char(char const *name, int i)
{
    if (should_uppercase_in_firstname(name, i)) {
        my_putchar(to_upper(name[i]));
    } else {
        my_putchar(to_lower(name[i]));
    }
}

static void process_last_name_char(char c)
{
    my_putchar(to_upper(c));
}

static void handle_space(int *in_first_name)
{
    *in_first_name = 0;
}

int format_french_name(char const *name)
{
    int i = 0;
    int in_first_name = 1;

    while (name[i] != '\0') {
        if (is_space(name[i])) {
            handle_space(&in_first_name);
            my_putchar(name[i]);
            i++;
            continue;
        }
        if (in_first_name)
            process_first_name_char(name, i);
        else
            process_last_name_char(name[i]);
        i++;
    }
    my_putchar('\n');
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        write(2, "Usage: frenchNameFormatter string\n", 35);
        return 84;
    }
    return format_french_name(argv[1]);
}
