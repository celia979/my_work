/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Flag -a implementation
*/

#include "include/my.h"

static void print_entry(char const *filepath, char *name, int flags)
{
    if (flags & FLAG_L)
        print_long_format(filepath, name);
    else {
        my_putstr(name);
        my_putchar(' ');
    }
}

static void print_entries(char const *filepath, struct dirent **entries,
    int count, int flags)
{
    int i = 0;

    while (i < count) {
        print_entry(filepath, entries[i]->d_name, flags);
        free(entries[i]);
        i++;
    }
    if (!(flags & FLAG_L))
        my_putchar('\n');
}

static int should_skip(char const *name, int flags)
{
    if (!(flags & FLAG_A) && name[0] == '.')
        return 1;
    return 0;
}

int error(const char *filepath)
{
    perror(filepath);
    return 84;
}

int flag_a(char const *filepath, int flags)
{
    DIR *dir = opendir(filepath);
    struct dirent *entry = NULL;
    struct dirent **entries = malloc(sizeof(struct dirent *) * 128);
    int count = 0;

    if (dir == NULL)
        return error(filepath);
    entry = readdir(dir);
    while (entry != NULL) {
        if (should_skip(entry->d_name, flags))
            continue;
        entries[count] = malloc(sizeof(struct dirent));
        my_strcpy(entries[count]->d_name, entry->d_name);
        count++;
        entry = readdir(dir);
    }
    closedir(dir);
    print_entries(filepath, entries, count, flags);
    free(entries);
    return 0;
}
