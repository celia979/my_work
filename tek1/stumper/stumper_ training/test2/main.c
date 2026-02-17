/*
** EPITECH PROJECT, 2026
** US Name Formatter
** File description:
** Main file for US Name Formatter program
*/

#include "my.h"
#include <unistd.h>

static void print_two_letter_name(char const *str)
{
    my_putchar(to_upper(str[0]));
    my_putchar(to_upper(str[1]));
}

static void print_first_name(char const *str, int len)
{
    int i = 1;

    if (len == 2)
        return print_two_letter_name(str);
    my_putchar(to_upper(str[0]));
    while (i < len) {
        my_putchar(to_lower(str[i]));
        i++;
    }
}

static void print_initial(char c)
{
    my_putchar(to_upper(c));
    my_putchar('.');
}

static void print_last_name_word(char const *str, int len)
{
    int i = 1;

    my_putchar(to_upper(str[0]));
    while (i < len) {
        my_putchar(to_lower(str[i]));
        i++;
    }
}

static int skip_spaces(char const *str, int i)
{
    while (is_space(str[i]))
        i++;
    return i;
}

static int process_first_name(char const *name)
{
    int i = 0;
    int len = get_word_length(name);

    print_first_name(name, len);
    i = skip_spaces(name, len);
    return i;
}

static int process_initial(char const *name, int i)
{
    int len = get_word_length(&name[i]);

    if (name[i] != '\0' && len == 1) {
        my_putchar(' ');
        print_initial(name[i]);
        i = skip_spaces(name, i + 1);
    }
    return i;
}

static void process_last_names(char const *name, int i)
{
    int len = 0;

    while (name[i] != '\0') {
        my_putchar(' ');
        len = get_word_length(&name[i]);
        print_last_name_word(&name[i], len);
        i = skip_spaces(name, i + len);
    }
}

static void format_name(char const *name)
{
    int i = 0;

    i = process_first_name(name);
    i = process_initial(name, i);
    process_last_names(name, i);
    my_putchar('\n');
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        write(1, "Usage: USNameFormatter string\n", 31);
        return 84;
    }
    format_name(argv[1]);
    return 0;
}
