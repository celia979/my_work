/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Flag -R implementation
*/

#include "include/my.h"

static int is_special_dir(char const *name)
{
    if (name[0] == '.' && name[1] == '\0')
        return 1;
    if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
        return 1;
    return 0;
}

static void list_directory(char const *path, int flags)
{
    my_putstr(path);
    my_putstr(":\n");
    flag_a(path, flags & ~FLAG_R_MAJ);
    my_putchar('\n');
}

static void build_subpath(char *path, char const *filepath, char const *name)
{
    my_strcpy(path, filepath);
    my_strcpy(path + my_strlen(path), "/");
    my_strcpy(path + my_strlen(path), name);
}

static int should_recurse(char const *name, int flags)
{
    if (is_special_dir(name))
        return 0;
    if (!(flags & FLAG_A) && name[0] == '.')
        return 0;
    return 1;
}

static void recurse_dirs(char const *filepath, int flags)
{
    DIR *dir = opendir(filepath);
    struct dirent *entry = NULL;
    struct stat info;
    char path[1024];

    if (dir == NULL)
        return;
    entry = readdir(dir);
    while (entry != NULL) {
        if (!should_recurse(entry->d_name, flags))
            continue;
        build_subpath(path, filepath, entry->d_name);
        if (lstat(path, &info) == 0 && S_ISDIR(info.st_mode)) {
            my_putchar('\n');
            list_directory(path, flags);
            recurse_dirs(path, flags);
        }
    }
    closedir(dir);
}

int flag_r_maj(char const *filepath, int flags)
{
    list_directory(filepath, flags);
    recurse_dirs(filepath, flags);
    return 0;
}
