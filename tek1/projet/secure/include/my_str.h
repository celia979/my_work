/*
** EPITECH PROJECT, 2026
** my_str
** File description:
** all str fct
*/

#include <stdlib.h>

#ifndef MY_STR_H_
    #define MY_STR_H_

char *my_strcat(char *s1, char const *s2);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(const char *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strtoi(char *str);
double my_strtof(char *str);

#endif /* !MY_STR_H_ */
