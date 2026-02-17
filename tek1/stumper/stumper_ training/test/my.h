/*
** EPITECH PROJECT, 2026
** B-CPE-210
** File description:
** Header file for French Name Formatter project
*/

#ifndef FRENCH_NAME_FORMATTER_H
    #define FRENCH_NAME_FORMATTER_H

    #include <unistd.h>

int format_french_name(char const *name);
void print_error_message(void);
char to_upper(char c);
char to_lower(char c);
int is_alpha(char c);
int is_space(char c);
int my_strlen(char const *str);
void my_putchar(char c);

#endif
