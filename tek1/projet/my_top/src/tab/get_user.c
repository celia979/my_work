/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get_user
*/

#include "my.h"

char *get_user_2(FILE *file, char *uid)
{
    size_t size = 0;
    char *line = "";
    char *num;
    char *user;

    while ((getline(&line, &size, file) != -1)) {
        user = my_strdup(strtok(line, ":"));
        strtok(NULL, ":");
        num = strtok(NULL, ":");
        if (my_strcmp(num, uid) == 0) {
            free(line);
            return user;
        } else
            free(user);
    }
    free(line);
    return my_strdup("Unknow");
}

char *get_user(char *uid)
{
    FILE *file = fopen("/etc/passwd", "r");
    char *user;

    user = get_user_2(file, uid);
    fclose(file);
    return user;
}
